cmake_minimum_required(VERSION 3.16)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MARGO REQUIRED IMPORTED_TARGET GLOBAL margo)
pkg_check_modules(LTTNGUST REQUIRED IMPORTED_TARGET GLOBAL lttng-ust)

add_library (starch_monitor MODULE
    margo-lttng-monitoring.c
    margo-lttng-tp.c
)

set_target_properties(starch_monitor PROPERTIES
    PREFIX ""
)

target_include_directories(starch_monitor
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(starch_monitor PRIVATE
        PkgConfig::LTTNGUST
        dl
        PkgConfig::MARGO
)
