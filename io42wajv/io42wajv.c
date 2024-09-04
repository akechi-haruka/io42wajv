#include <windows.h>

#include <stdbool.h>
#include <stdint.h>
#include <winuser.h>
#include <subprojects/segapi/api/api.h>

#include "io42wajv/io42wajv.h"
#include "io42wajv/config.h"
#include "io42wajv/io4.h"
#include "io42wajv/util/dprintf.h"
#include "wajv.h"

#define MIN_API_VER 0x010101

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

    if (api_get_version() < MIN_API_VER){
        dprintf("io42wajv: API dll is outdated! At least v.%x is required, DLL is v.%x", MIN_API_VER, api_get_version());
        return FALSE;
    }

    io42wajv_config_load(&cfg, ".\\io42wajv.ini");

    api_init(".\\io42wajv.ini");

    wajv_init(&cfg);

    dprintf("io42wajv: Loaded\n");

    return TRUE;
}
