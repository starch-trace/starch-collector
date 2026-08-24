#undef LTTNG_UST_TRACEPOINT_PROVIDER
#define LTTNG_UST_TRACEPOINT_PROVIDER margo_rpc

#undef LTTNG_UST_TRACEPOINT_INCLUDE
#define LTTNG_UST_TRACEPOINT_INCLUDE "./margo-lttng-tp-rpc.h"

#if !defined(_MARGO_LTTNG_TP_RPC_H) || defined(LTTNG_UST_TRACEPOINT_HEADER_MULTI_READ)
#define _MARGO_LTTNG_TP_RPC_H

#include <stdint.h>
#include <lttng/tracepoint.h>

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    register_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, rpc_id,
        // uint64_t, pool,
        const char*, rpc_name
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, rpc_id, rpc_id)
        // lttng_ust_field_integer_hex(uint64_t, pool, pool)
        lttng_ust_field_string(rpc_name, rpc_name)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    register_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, rpc_id
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, rpc_id, rpc_id)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)
/*
LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    deregister_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, rpc_id
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, rpc_id, rpc_id)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    deregister_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, rpc_id,
        int32_t, ret
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, rpc_id, rpc_id)
        lttng_ust_field_integer(int32_t, ret, ret)
    )
)
*/

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    lookup_begin,
    LTTNG_UST_TP_ARGS(
        const char*, name
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_string(name, name ? name : "(self)")
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    lookup_end,
    LTTNG_UST_TP_ARGS(
        const char*, name,
        uint64_t, addr
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, addr, addr)
        lttng_ust_field_string(name, name ? name : "(self)")
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    create_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, rpc_id
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, rpc_id, rpc_id)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    create_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, target_addr,
        uint64_t, handle
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, target_addr, target_addr)
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT( //#TODO:
    margo_rpc,
    forward_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, request,
        uint64_t, correlation_id
        //uint16_t, provider_id,
        //uint32_t, timeout_ms,
        //uint64_t, data TODO:
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, request, request)
        lttng_ust_field_integer_hex(uint64_t, correlation_id, correlation_id)
        //lttng_ust_field_integer(uint16_t, provider_id, provider_id)
        //lttng_ust_field_integer(uint32_t, timeout_ms, timeout_ms)
        //lttng_ust_field_integer_hex(uint64_t, data, data) TODO:
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    forward_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle
#ifdef MARGO_LTTNG_RET_TRACING
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
#ifdef MARGO_LTTNG_RET_TRACING
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT( // #TODO:
    margo_rpc,
    forward_cb_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, request,
        uint64_t, info
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, request, request)
        lttng_ust_field_integer_hex(uint64_t, info, info)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    forward_cb_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, request
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, request, request)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    respond_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, request
        // uint32_t, timeout_ms,
        // uint8_t, error,
        // uint64_t, data
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, request, request)
        //lttng_ust_field_integer(uint32_t, timeout_ms, timeout_ms)
        //lttng_ust_field_integer(uint8_t, error, error)
        //lttng_ust_field_integer_hex(uint64_t, data, data)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    respond_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle
#ifdef MARGO_LTTNG_RET_TRACING
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
#ifdef MARGO_LTTNG_RET_TRACING
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    respond_cb_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, request,
        uint64_t, info
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, request, request)
        lttng_ust_field_integer_hex(uint64_t, info, info)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    respond_cb_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, request
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, request, request)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    destroy_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    destroy_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    rpc_handler_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        const char*, origin_addr,
        uint64_t, parent_rpc_id,
        uint64_t, parent_trace_id
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_string(origin_addr, origin_addr)
        lttng_ust_field_integer_hex(uint64_t, parent_rpc_id, parent_rpc_id)
        lttng_ust_field_integer_hex(uint64_t, parent_trace_id, parent_trace_id)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    rpc_handler_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, pool
#ifdef MARGO_LTTNG_RET_TRACING
       , int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, pool, pool)
#ifdef MARGO_LTTNG_RET_TRACING
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    rpc_ult_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    rpc_ult_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    set_input_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle,
        uint64_t, request,
        uint64_t, data
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
        lttng_ust_field_integer_hex(uint64_t, request, request)
        lttng_ust_field_integer_hex(uint64_t, data, data)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    set_input_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    set_output_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle,
        uint64_t, request,
        uint64_t, data
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
        lttng_ust_field_integer_hex(uint64_t, request, request)
        lttng_ust_field_integer_hex(uint64_t, data, data)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    set_output_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    get_input_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, data,
        uint64_t, parent_handle
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, data, data)
        lttng_ust_field_integer_hex(uint64_t, parent_handle, parent_handle)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    get_input_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle
#ifdef MARGO_LTTNG_RET_TRACING
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
#ifdef MARGO_LTTNG_RET_TRACING
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    get_output_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle,
        uint64_t, data
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
        lttng_ust_field_integer_hex(uint64_t, data, data)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    get_output_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, trace_handle
#ifdef MARGO_LTTNG_RET_TRACING
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, trace_handle, trace_handle)
#ifdef MARGO_LTTNG_RET_TRACING
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    free_input_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle,
        uint64_t, data
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
        lttng_ust_field_integer_hex(uint64_t, data, data)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    free_input_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    free_output_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle,
        uint64_t, data
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
        lttng_ust_field_integer_hex(uint64_t, data, data)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_rpc,
    free_output_end,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

#endif /* _MARGO_LTTNG_TP_RPC_H */

#include <lttng/tracepoint-event.h>
