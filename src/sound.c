#include "hal_data.h"
#include "sound.h"

const unsigned char *const sound[2] = {arrival, warning};
const int size[2] = {sizeof arrival, sizeof warning};

void play_sound(int which) {
    unsigned const char *soundData = sound[which];

    R_DAC_Open(&g_dac0_ctrl, &g_dac0_cfg);
    R_DAC_Start(&g_dac0_ctrl);
    uint16_t value;
    for (int i = 0; i < size[which]; i += 2) {
        value = (uint16_t)(soundData[i] | (soundData[i + 1] << 8));
        R_DAC_Write(&g_dac0_ctrl, value);
        R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MICROSECONDS);
    }
}