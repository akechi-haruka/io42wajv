#include <windows.h>

#include <stdbool.h>
#include <stdint.h>
#include <winuser.h>

#include "io42wajv/io42wajv.h"
#include "io42wajv/config.h"
#include "io42wajv/io4.h"
#include "io42wajv/util/dprintf.h"
#include "wajv.h"

struct io42wajv_config cfg;

struct io42wajv_config shared_get_config(){
    return cfg;
}

BOOL WINAPI DllMain(HMODULE mod, DWORD cause, void *ctx)
{

    if (cause != DLL_PROCESS_ATTACH) {
        return TRUE;
    }

    dprintf("io42wajv: Initializing\n");

    io42wajv_config_load(&cfg, ".\\io42wajv.ini");

    wajv_init(&cfg);

    dprintf("io42wajv: Loaded\n");

    return TRUE;
}
