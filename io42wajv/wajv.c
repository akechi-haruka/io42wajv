#include <windows.h>
#include <stdint.h>

#include "io42wajv/wajv.h"
#include "util/dprintf.h"
#include "io42wajv.h"

static struct WAJVInput* input_emu;
static struct io42wajv_config* config;
struct JVSUSBReportIn report;

static bool coin_was_down = false;
static bool test_was_down = false;

void wajv_init(struct io42wajv_config* cfg){
    config = cfg;
}

DWORD WINAPI polling_thread(void* data) {
    dprintf("io42wajv: I/O Polling Thread started\n");
    while (true){

        if (FAILED(io4_hid_poll(&report))){
            dprintf("io42wajv: ERROR: I/O polling failed!\n");
            return 1;
        }

        Sleep(1);
    }

    dprintf("io42wajv: I/O Polling Thread stopped\n");
    return 0;
}

inline int shared_get_io4_btn(int btn){
    int p = btn / 16;
    int b = btn % 16;
    int v = ((report.buttons[p] >> b) & 1);
    return v != 0;
}

__stdcall int WAJVOpen(int x){
    dprintf("WAJV: WAJVOpen\n");

    input_emu = (WAJVInput*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WAJVInput));

    HRESULT hr = io4_hid_init();

    if (FAILED(hr)){
        dprintf("io42wajv: io4 init failed: %ld\n", hr);
        return 0;
    }

    dprintf("io42wajv: IO4 connected\n");

    CreateThread(NULL, 0, polling_thread, NULL, 0, NULL);

    hr = io4_clear_board_status();
    if (FAILED(hr)){
        dprintf("io42wajv: io4 reset failed: %ld\n", hr);
        return 0;
    }


    struct JVSUSBReportGPIOOut clear_leds = {};
    hr = io4_set_gpio(clear_leds);

    if (FAILED(hr)){
        dprintf("io42wajv: io4 led clear failed: %ld\n", hr);
        return 0;
    }

    dprintf("io42wajv: Successfully connected to IO4\n");

    // immediately set the side to prevent race conditions with the second cab
    input_emu->SwIn[0][7] = config->sync.side;

    return 1;
}
__stdcall signed int WAJVGetStatus(){
    //dprintf("WAJV: WAJVGetStatus\n");
    return 1;
}
__stdcall int WAJVSetFunctionSettings(int a1, int a2, int a3){
    dprintf("WAJV: WAJVSetFunctionSettings: %d, %d, %d\n", a1, a2, a3);
    return 1;
}
__stdcall int WAJVUpdate(){
    dprintf("WAJV: WAJVUpdate\n");
    return 1;
}
__stdcall WAJVInput* WAJVGetInput(int x){
    //dprintf("WAJV: WAJVGetInput\n");
    return input_emu;
}
__stdcall const char *WAJVGetLibraryVersion(){
    return "io42wajv";
}
__stdcall int WAJVClose(){
    dprintf("WAJV: WAJVClose\n");
    return 1;
}

__stdcall int WAJVEndUpdate(){
    //dprintf("WAJV: WAJVEndUpdate\n");
    input_emu->DipSw1 = config->dipsw1;
    input_emu->DipSw2 = config->dipsw2;
    input_emu->DipSw3 = config->dipsw3;
    input_emu->DipSw4 = config->dipsw4;

    int tbtn = config->test_switch;
    bool test_down = false;
    if (tbtn > -1) {
        test_down = shared_get_io4_btn(tbtn);
    }
    if (config->test_switch_mode == 1) {
        if (test_down) {
            if (!test_was_down) {
                input_emu->SwTest = !input_emu->SwTest;
                test_was_down = true;
            }
        } else {
            test_was_down = false;
        }
    } else {
        input_emu->SwTest = test_down;
    }

    if (config->coin_chute > -1){
        input_emu->Coin[0].Count = report.chutes[config->coin_chute];
    } else {
        bool coin_down = GetAsyncKeyState(config->coin_keyboard_button) & 0x8000;
        if (coin_down){
            if (!coin_was_down){
                input_emu->Coin[0].Status = WAJVCoinBusy;
                coin_was_down = true;
            }
        } else {
            coin_was_down = false;
            input_emu->Coin[0].Status = WAJVCoinOK;
        }
    }

    for (int x = 0; x < MAX_X; x++){
        for (int y = 0; y < MAX_Y; y++) {
            int btn = config->inputs[x][y];
            if (btn > -1) {
                input_emu->SwIn[x][y] = shared_get_io4_btn(btn);
            }
        }
    }

    for (int i = 0; i < 4; i++){
        input_emu->Service[i].Status = WAJVServiceOK;
    }

	input_emu->SwIn[0][7] = config->sync.side;

    return 1;
}
__stdcall int WAJVSetOutput(int a1, WAJVOutput* a2){
    //dprintf("WAJV: WAJVSetOutput: %d, %p\n", a1, a2);
    //dprintf("AnalogOut: %d, %d, %d, %d, %d, %d, %d, %d", a2->AnalogOut[0], a2->AnalogOut[1], a2->AnalogOut[2], a2->AnalogOut[3], a2->AnalogOut[4], a2->AnalogOut[5], a2->AnalogOut[6], a2->AnalogOut[7]);
    return 1;
}
__stdcall int WAJVBeginUpdate(){
    //dprintf("WAJV: WAJVBeginUpdate\n");
    return 1;
}
__stdcall signed int WAJVGetNodeCount(){
    //dprintf("WAJV: WAJVGetNodeCount\n");
    return 99;
}
__stdcall int WAJVSetPLParm(unsigned __int8 a1, __int16 a2, unsigned __int8 a3){
    dprintf("WAJV: WAJVSetPLParm: %d, %d, %d\n", a1, a2, a3);
    return 1;
}
