#undef LTTNG_UST_TRACEPOINT_PROVIDER
#define LTTNG_UST_TRACEPOINT_PROVIDER margo_core

#undef LTTNG_UST_TRACEPOINT_INCLUDE
#define LTTNG_UST_TRACEPOINT_INCLUDE "./margo-lttng-tp-core.h"

#if !defined(_MARGO_LTTNG_TP_CORE_H) || defined(LTTNG_UST_TRACEPOINT_HEADER_MULTI_READ)
#define _MARGO_LTTNG_TP_CORE_H

#include <stdint.h>
#include <lttng/tracepoint.h>

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    init,
    LTTNG_UST_TP_ARGS(
        uint64_t, mid,
        const char*, addr
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, mid, mid)
        lttng_ust_field_string(addr, addr)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    progress_begin,
    LTTNG_UST_TP_ARGS(
        // uint32_t, timeout_ms
    ),
    LTTNG_UST_TP_FIELDS(
        // lttng_ust_field_integer(uint32_t, timeout_ms, timeout_ms)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    progress_end,
    LTTNG_UST_TP_ARGS(
        #ifdef LTTNG_ENABLE_RET_TRACING
        int32_t, ret
        #endif
    ),
    LTTNG_UST_TP_FIELDS(
#ifdef MARGO_LTTNG_RET_TRACING 
    lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    trigger_begin,
    LTTNG_UST_TP_ARGS(
        // uint32_t, timeout_ms,
        // uint32_t, max_count
    ),
    LTTNG_UST_TP_FIELDS(
        // lttng_ust_field_integer(uint32_t, timeout_ms, timeout_ms)
        // lttng_ust_field_integer(uint32_t, max_count, max_count)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    trigger_end,
    LTTNG_UST_TP_ARGS(
        uint32_t, actual_count
#ifdef MARGO_LTTNG_RET_TRACING 
        ,int32_t, ret
#endif
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer(uint32_t, actual_count, actual_count)
#ifdef MARGO_LTTNG_RET_TRACING 
        lttng_ust_field_integer(int32_t, ret, ret)
#endif
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    wait_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    wait_end,
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
    margo_core,
    sleep_begin,
    LTTNG_UST_TP_ARGS(
        // uint32_t, timeout_ms
    ),
    LTTNG_UST_TP_FIELDS(
        // lttng_ust_field_integer(uint32_t, timeout_ms, timeout_ms)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_core,
    sleep_end,
    LTTNG_UST_TP_ARGS()
    ,
    LTTNG_UST_TP_FIELDS()
)

#endif /* _MARGO_LTTNG_TP_CORE_H */

#include <lttng/tracepoint-event.h>
