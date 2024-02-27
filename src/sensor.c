#include "hal_data.h"
#include "sensor.h"

void init_resistor(void) {
	R_ADC_Open(&g_adc0_ctrl, &g_adc0_cfg);
    R_ADC_ScanCfg(&g_adc0_ctrl, &g_adc0_channel_cfg);
}

uint16_t read_resistor(void) {
    R_ADC_ScanStart(&g_adc0_ctrl);
    adc_status_t status;
    status.state = ADC_STATE_SCAN_IN_PROGRESS;
    while (ADC_STATE_SCAN_IN_PROGRESS == status.state)
        R_ADC_StatusGet(&g_adc0_ctrl, &status);

    uint16_t pos;
    R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_0, &pos);
    double voltage = pos * (3.3 / 4096) * 1000;
    double rb      = voltage * 3.0303;
    return (uint16_t)(rb + 0.5);
}