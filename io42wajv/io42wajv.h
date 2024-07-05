#pragma once

#include <windows.h>

#include <stdbool.h>
#include <stdint.h>

#include "io42wajv/config.h"
#include "io42wajv/io4.h"

int shared_get_io4_btn(int index);
void shared_poll(uint8_t *opbtn, uint8_t *gamebtn);
