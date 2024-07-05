#pragma once

#include <stddef.h>
#include <stdint.h>

#include <stdbool.h>

#define MAX_X 64
#define MAX_Y 4

struct sync_config {
    uint8_t side;
};

struct io42wajv_config {
    int inputs[MAX_X][MAX_Y];

    uint8_t coin_keyboard_button;
    int coin_chute;

    uint8_t test_switch_mode;
    uint8_t test_switch;

    uint8_t dipsw1;
    uint8_t dipsw2;
    uint8_t dipsw3;
    uint8_t dipsw4;

    struct sync_config sync;
};

void io42wajv_config_load(
        struct io42wajv_config *cfg,
        const char *filename);
