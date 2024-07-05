#include <windows.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include "io42wajv/util/dprintf.h"
#include "io42wajv/config.h"

void io42wajv_config_load(
        struct io42wajv_config *cfg,
        const char *filename)
{
    assert(cfg != NULL);
    assert(filename != NULL);

    for (int x = 0; x < MAX_X; x++){
        for (int y = 0; y < MAX_Y; y++) {
            char bstr[16];
            sprintf(bstr, "button%d_%d", x, y);
            cfg->inputs[x][y] = GetPrivateProfileIntA("player", bstr, -1, filename);
        }
    }

    cfg->test_switch_mode = GetPrivateProfileIntA("system", "test_switch_mode", 0, filename);
    cfg->test_switch = GetPrivateProfileIntA("system", "test_switch", -1, filename);

    cfg->dipsw1 = GetPrivateProfileIntA("dipsw", "dipsw1", 0, filename);
    cfg->dipsw2 = GetPrivateProfileIntA("dipsw", "dipsw2", 0, filename);
    cfg->dipsw3 = GetPrivateProfileIntA("dipsw", "dipsw3", 0, filename);
    cfg->dipsw4 = GetPrivateProfileIntA("dipsw", "dipsw4", 0, filename);

    cfg->coin_keyboard_button = GetPrivateProfileIntA("coin", "keyboard", '1', filename);
    cfg->coin_chute = GetPrivateProfileIntA("coin", "chute", -1, filename);

    char side[2];

    GetPrivateProfileStringA(
            "wajv",
            "side",
            "L",
            side,
            _countof(side),
            filename);

    if (strcmp(side, "R") == 0){
        cfg->sync.side = 1;
    } else if (strcmp(side, "L") != 0){
        dprintf("WARNING: Unknown side value \"%s\", defaulting to L!\n", side);
    }
}
