io42wajv = shared_library(
    'io42wajv',
    name_prefix : '',
    include_directories : inc,
    implicit_include_directories : false,
    c_pch : '../precompiled.h',
    vs_module_defs : 'exports.def',
    link_with : [
    ],
    dependencies : [
        hidapi_dep
    ],
    sources : [
        'io42wajv.c',
        'io42wajv.h',
        'config.c',
        'config.h',
        'io4.c',
        'io4.h',
        'wajv.c',
        'wajv.h',
        'util/dprintf.c',
        'util/dprintf.h',
    ],
)
