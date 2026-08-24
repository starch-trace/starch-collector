#undef LTTNG_UST_TRACEPOINT_PROVIDER
#define LTTNG_UST_TRACEPOINT_PROVIDER margo_bulk

#undef LTTNG_UST_TRACEPOINT_INCLUDE
#define LTTNG_UST_TRACEPOINT_INCLUDE "./margo-lttng-tp-bulk.h"

#if !defined(_MARGO_LTTNG_TP_BULK_H) || defined(LTTNG_UST_TRACEPOINT_HEADER_MULTI_READ)
#define _MARGO_LTTNG_TP_BULK_H

#include <stdint.h>
#include <lttng/tracepoint.h>

LTTNG_UST_TRACEPOINT_EVENT(
    margo_bulk,
    bulk_create_begin,
    LTTNG_UST_TP_ARGS(
        uint32_t, count,
        uint64_t, ptrs,
        uint64_t, sizes,
        uint8_t, flags,
        uint64_t, attrs
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer(uint32_t, count, count)
        lttng_ust_field_integer_hex(uint64_t, ptrs, ptrs)
        lttng_ust_field_integer_hex(uint64_t, sizes, sizes)
        lttng_ust_field_integer(uint8_t, flags, flags)
        lttng_ust_field_integer_hex(uint64_t, attrs, attrs)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_bulk,
    bulk_create_end,
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
    margo_bulk,
    bulk_transfer_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, request,
        int32_t, op,
        uint64_t, origin_addr,
        uint64_t, origin_handle,
        uint64_t, origin_offset,
        uint64_t, local_handle,
        uint64_t, local_offset,
        uint64_t, size,
        uint32_t, timeout_ms
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, request, request)
        lttng_ust_field_integer(int32_t, op, op)
        lttng_ust_field_integer_hex(uint64_t, origin_addr, origin_addr)
        lttng_ust_field_integer_hex(uint64_t, origin_handle, origin_handle)
        lttng_ust_field_integer(uint64_t, origin_offset, origin_offset)
        lttng_ust_field_integer_hex(uint64_t, local_handle, local_handle)
        lttng_ust_field_integer(uint64_t, local_offset, local_offset)
        lttng_ust_field_integer(uint64_t, size, size)
        lttng_ust_field_integer(uint32_t, timeout_ms, timeout_ms)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_bulk,
    bulk_transfer_end,
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
    margo_bulk,
    bulk_transfer_cb_begin,
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
    margo_bulk,
    bulk_transfer_cb_end,
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
    margo_bulk,
    bulk_free_begin,
    LTTNG_UST_TP_ARGS(
        uint64_t, handle
    ),
    LTTNG_UST_TP_FIELDS(
        lttng_ust_field_integer_hex(uint64_t, handle, handle)
    )
)

LTTNG_UST_TRACEPOINT_EVENT(
    margo_bulk,
    bulk_free_end,
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

#endif /* _MARGO_LTTNG_TP_BULK_H */

#include <lttng/tracepoint-event.h>
