/**

 * (C) 2022 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <string.h>
#include <unistd.h>
#include <margo.h>
#include "margo-monitoring.h"
#ifdef __clang_analyzer__
    // Prevent clang-analyzer from getting confused by the actual HASH_JEN
    // macro. This trivial HASH_FUNCTION is not actually used when the code is
    // compiled.
    #define HASH_FUNCTION(keyptr, keylen, hashv) hashv = 0
#endif
#include "margo-lttng-tp-core.h"
#include "margo-lttng-tp-rpc.h"
#include "margo-lttng-tp-bulk.h"

/* ========================================================================
 * Functions related to implementing the monitor's callbacks
 * ======================================================================== */

static void* __margo_lttng_monitor_initialize(margo_instance_id   mid,
                                                void*               uargs,
                                                struct json_object* config)
{
    hg_addr_t self;
    margo_addr_self(mid, &self);

    hg_size_t bufsize = 128;
    char buf[128];
    HG_Addr_to_string(margo_get_class(mid), buf, &bufsize, self);
    margo_addr_free(mid, self);

    lttng_ust_tracepoint(margo_core, init, mid, buf);
}

static void __margo_lttng_monitor_finalize(void* uargs)
{
    
}

static const char* __margo_lttng_monitor_name() { return "lttng"; }

static struct json_object* __margo_lttng_monitor_config(void* uargs)
{
    
}

static void
__margo_lttng_monitor_on_register(void*                         uargs,
                                    double                        timestamp,
                                    margo_monitor_event_t         event_type,
                                    margo_monitor_register_args_t event_args)
{
    if(event_type == MARGO_MONITOR_FN_START) lttng_ust_tracepoint(margo_rpc, register_begin, event_args->id, event_args->name);
    else lttng_ust_tracepoint(margo_rpc, register_end, event_args->id);
}

static void
__margo_lttng_monitor_on_progress(void*                         uargs,
                                    double                        timestamp,
                                    margo_monitor_event_t         event_type,
                                    margo_monitor_progress_args_t event_args)
{
    if(event_type == MARGO_MONITOR_FN_START) lttng_ust_tracepoint(margo_core, progress_begin);
    else lttng_ust_tracepoint(margo_core, progress_end);
}

static void
__margo_lttng_monitor_on_trigger(void*                        uargs,
                                   double                       timestamp,
                                   margo_monitor_event_t        event_type,
                                   margo_monitor_trigger_args_t event_args)
{
    if(event_type == MARGO_MONITOR_FN_START) lttng_ust_tracepoint(margo_core, trigger_begin);
    else lttng_ust_tracepoint(margo_core, trigger_end, event_args->actual_count);
}

static void
__margo_lttng_monitor_on_lookup(void* uargs, double timestamp, margo_monitor_event_t event_type, margo_monitor_lookup_args_t event_args)
{
    if(event_type == MARGO_MONITOR_FN_START) return;
    
    lttng_ust_tracepoint(margo_rpc, lookup_end, event_args->name, event_args->addr);
}

static _Atomic uint64_t global_index = 0;
static void
__margo_lttng_monitor_on_create(void*                       uargs,
                                  double                      timestamp,
                                  margo_monitor_event_t       event_type,
                                  margo_monitor_create_args_t event_args)
{
    uint64_t trace_handle = -1;
    char AddrBuf[64] = { 0 };
    size_t BufSize = 64;
    if(event_type == MARGO_MONITOR_FN_START)
    {
        trace_handle = ++global_index;
        event_args->uctx.i = trace_handle;
        lttng_ust_tracepoint(margo_rpc, create_begin, trace_handle, event_args->id);
        return;
    }
    else trace_handle = event_args->uctx.i;
    const struct hg_info* handle_info = margo_get_info(event_args->handle);
    if(!handle_info) return;
    margo_monitor_data_t trace_data = {.i = (int64_t)trace_handle};
    margo_set_monitoring_data(event_args->handle, trace_data);
    lttng_ust_tracepoint(margo_rpc, create_end, trace_handle, handle_info->addr, event_args->handle);
}

#define RETRIEVE_SESSION(handle)                                            \
    session_t* session = NULL;                                              \
    do {                                                                    \
        margo_monitor_data_t monitor_data;                                  \
        hg_return_t ret = margo_get_monitoring_data(handle, &monitor_data); \
        (void)ret;                                                          \
        session = (session_t*)monitor_data.p;                               \
    } while (0)

#define RETRIEVE_BULK_SESSION(request)                                   \
    bulk_session_t* session = NULL;                                      \
    do {                                                                 \
        margo_monitor_data_t monitor_data;                               \
        hg_return_t          ret                                         \
            = margo_request_get_monitoring_data(request, &monitor_data); \
        (void)ret;                                                       \
        session = (bulk_session_t*)monitor_data.p;                       \
    } while (0)

static uint64_t get_trace_handle(hg_handle_t handle)
{
    margo_monitor_data_t monitor_data;
    margo_get_monitoring_data(handle, &monitor_data);
    return (uint64_t)monitor_data.i;
}

static void
__margo_lttng_monitor_on_forward(void*                        uargs,
                                   double                       timestamp,
                                   margo_monitor_event_t        event_type,
                                   margo_monitor_forward_args_t event_args)
{
    uint64_t trace_handle = get_trace_handle(event_args->handle);
    if(event_type == MARGO_MONITOR_FN_START)
    {
        lttng_ust_tracepoint(margo_rpc, forward_begin, trace_handle, event_args->request, event_args->trace_id);
    }
    else
    {
        lttng_ust_tracepoint(margo_rpc, forward_end, trace_handle);
    }

}

static void
__margo_lttng_monitor_on_set_input(void*                          uargs,
                                     double                         timestamp,
                                     margo_monitor_event_t          event_type,
                                     margo_monitor_set_input_args_t event_args)
{
}

static void __margo_lttng_monitor_on_set_output(
    void*                           uargs,
    double                          timestamp,
    margo_monitor_event_t           event_type,
    margo_monitor_set_output_args_t event_args)
{
}

static void __margo_lttng_monitor_on_get_output(
    void*                           uargs,
    double                          timestamp,
    margo_monitor_event_t           event_type,
    margo_monitor_get_output_args_t event_args)
{
    uint64_t trace_handle = get_trace_handle(event_args->handle);
    if(event_type == MARGO_MONITOR_FN_START)
    {
        lttng_ust_tracepoint(margo_rpc, get_output_begin, trace_handle, event_args->data);
    }
    else
    {
        lttng_ust_tracepoint(margo_rpc, get_output_end, trace_handle);
    }
}

static void
__margo_lttng_monitor_on_get_input(void*                          uargs,
                                     double                         timestamp,
                                     margo_monitor_event_t          event_type,
                                     margo_monitor_get_input_args_t event_args)
{
    uint64_t trace_handle = get_trace_handle(event_args->handle);
    if(event_type == MARGO_MONITOR_FN_START)
    {
        lttng_ust_tracepoint(margo_rpc, get_input_begin, trace_handle, event_args->parent_handle, event_args->data);
    }
    else
    {
        lttng_ust_tracepoint(margo_rpc, get_input_end, trace_handle);
    }
}

static void __margo_lttng_monitor_on_forward_cb(
    void*                           uargs,
    double                          timestamp,
    margo_monitor_event_t           event_type,
    margo_monitor_forward_cb_args_t event_args)
{
    //lttng_ust_tracepoint(margo, c_rpc_forward_cb, event_args->handle, event_type);
}

static void
__margo_lttng_monitor_on_respond(void*                        uargs,
                                   double                       timestamp,
                                   margo_monitor_event_t        event_type,
                                   margo_monitor_respond_args_t event_args)
{
    uint64_t trace_handle = get_trace_handle(event_args->handle);
    if(event_type == MARGO_MONITOR_FN_START)
    {
        lttng_ust_tracepoint(margo_rpc, respond_begin, trace_handle, event_args->request);
    }
    else
    {
        lttng_ust_tracepoint(margo_rpc, respond_end, trace_handle);
    }
}

static void __margo_lttng_monitor_on_respond_cb(
    void*                           uargs,
    double                          timestamp,
    margo_monitor_event_t           event_type,
    margo_monitor_respond_cb_args_t event_args)
{
    
}

static void
__margo_lttng_monitor_on_wait(void*                     uargs,
                                double                    timestamp,
                                margo_monitor_event_t     event_type,
                                margo_monitor_wait_args_t event_args)
{
    
}

static void __margo_lttng_monitor_on_rpc_handler(
    void*                            uargs,
    double                           timestamp,
    margo_monitor_event_t            event_type,
    margo_monitor_rpc_handler_args_t event_args)
{
    size_t BufSize = 64;
    char AddrBuf[64] = { 0 };
    const struct hg_info* handle_info = margo_get_info(event_args->handle);
    if(handle_info) { HG_Addr_to_string(handle_info->hg_class, AddrBuf, &BufSize, handle_info->addr); }

    //lttng_ust_tracepoint(margo, rpc_handler_begin, event_args->parent_trace_id, event_args->handle, event_args->parent_rpc_id, AddrBuf, event_type);

    if(event_type == MARGO_MONITOR_FN_START)
    {
        /* first time this (server-side) handle is seen: mint its own trace_handle */
        uint64_t trace_handle = ++global_index;
        margo_monitor_data_t trace_data = {.i = (int64_t)trace_handle};
        margo_set_monitoring_data(event_args->handle, trace_data);

        lttng_ust_tracepoint(margo_rpc, rpc_handler_begin, trace_handle, AddrBuf, event_args->parent_rpc_id, event_args->parent_trace_id);
    }
    else
    {
        uint64_t trace_handle = get_trace_handle(event_args->handle);
        lttng_ust_tracepoint(margo_rpc, rpc_handler_end, trace_handle, event_args->pool);
    }
}

static void
__margo_lttng_monitor_on_rpc_ult(void*                        uargs,
                                   double                       timestamp,
                                   margo_monitor_event_t        event_type,
                                   margo_monitor_rpc_ult_args_t event_args)
{
    uint64_t trace_handle = get_trace_handle(event_args->handle);
    if(event_type == MARGO_MONITOR_FN_START)
    {
        lttng_ust_tracepoint(margo_rpc, rpc_ult_begin, trace_handle);
    }
    else
    {
        lttng_ust_tracepoint(margo_rpc, rpc_ult_end, trace_handle);
    }
}

static void
__margo_lttng_monitor_on_destroy(void*                        uargs,
                                   double                       timestamp,
                                   margo_monitor_event_t        event_type,
                                   margo_monitor_destroy_args_t event_args)
{
    
}

#define __MONITOR_FN(__event__)                                          \
    static void __margo_lttng_monitor_on_##__event__(                  \
        void* uargs, double timestamp, margo_monitor_event_t event_type, \
        margo_monitor_##__event__##_args_t event_args)

static void __margo_lttng_monitor_on_bulk_create(
    void*                            uargs,
    double                           timestamp,
    margo_monitor_event_t            event_type,
    margo_monitor_bulk_create_args_t event_args)
{
    
}

static void __margo_lttng_monitor_on_bulk_transfer(
    void*                              uargs,
    double                             timestamp,
    margo_monitor_event_t              event_type,
    margo_monitor_bulk_transfer_args_t event_args)
{
    
}

static void __margo_lttng_monitor_on_bulk_transfer_cb(
    void*                                 uargs,
    double                                timestamp,
    margo_monitor_event_t                 event_type,
    margo_monitor_bulk_transfer_cb_args_t event_args)
{
    
}

static void
__margo_lttng_monitor_on_add_pool(void*                         uargs,
                                    double                        timestamp,
                                    margo_monitor_event_t         event_type,
                                    margo_monitor_add_pool_args_t event_args)
{
    
}

static void __margo_lttng_monitor_on_remove_pool(
    void*                            uargs,
    double                           timestamp,
    margo_monitor_event_t            event_type,
    margo_monitor_remove_pool_args_t event_args)
{
    
}

static void __margo_lttng_monitor_on_add_xstream(
    void*                            uargs,
    double                           timestamp,
    margo_monitor_event_t            event_type,
    margo_monitor_add_xstream_args_t event_args)
{
    (void)uargs;
    (void)timestamp;
    (void)event_type;
    (void)event_args;
}

static void __margo_lttng_monitor_on_remove_xstream(
    void*                               uargs,
    double                              timestamp,
    margo_monitor_event_t               event_type,
    margo_monitor_remove_xstream_args_t event_args)
{
    (void)uargs;
    (void)timestamp;
    (void)event_type;
    (void)event_args;
}

#define __MONITOR_FN_EMPTY(__name__) \
    __MONITOR_FN(__name__)           \
    {                                \
        (void)uargs;                 \
        (void)timestamp;             \
        (void)event_args;            \
        (void)event_type;            \
    }

__MONITOR_FN_EMPTY(bulk_free)
__MONITOR_FN_EMPTY(deregister)
//__MONITOR_FN_EMPTY(lookup)
__MONITOR_FN_EMPTY(sleep)
__MONITOR_FN_EMPTY(free_input)
__MONITOR_FN_EMPTY(free_output)
__MONITOR_FN_EMPTY(prefinalize)
__MONITOR_FN_EMPTY(finalize)
__MONITOR_FN_EMPTY(user)

static hg_return_t __margo_lttng_monitor_dump(void*                 uargs,
                                                margo_monitor_dump_fn dump_fn,
                                                void*                 dump_args,
                                                bool                  reset)
{
    
}

struct margo_monitor __margo_lttng_monitor
    = {.uargs      = NULL,
       .initialize = __margo_lttng_monitor_initialize,
       .finalize   = __margo_lttng_monitor_finalize,
       .dump       = __margo_lttng_monitor_dump,
       .name       = __margo_lttng_monitor_name,
       .config     = __margo_lttng_monitor_config,
#define X(__x__, __y__) .on_##__y__ = __margo_lttng_monitor_on_##__y__,
       MARGO_EXPAND_MONITOR_MACROS
#undef X
};

struct margo_monitor* margo_lttng_monitor = &__margo_lttng_monitor;

int margo_monitor_init(struct margo_monitor** monitor)
{
    *monitor = margo_lttng_monitor;

    return 0;
}

