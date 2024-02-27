#include "hal_data.h"
#include "agt.h"

void init_agt(void) {
    R_AGT0->AGTMR1 = 0x41;
    R_AGT0->AGTMR2 = 0x00;
    R_AGT1->AGTMR1 = 0x41;
    R_AGT1->AGTMR2 = 0x00;
}

void start_agt0(void) {
    R_AGT_Open(&g_timer0_ctrl, &g_timer0_cfg);
    R_AGT_Start(&g_timer0_ctrl);
}

void stop_agt0(void) {
    R_AGT_Stop(&g_timer0_ctrl);
    R_AGT_Close(&g_timer0_ctrl);
}

void start_agt1(void) {
    R_AGT_Open(&g_timer1_ctrl, &g_timer1_cfg);
    R_AGT_Start(&g_timer1_ctrl);
}

void stop_agt1(void) {
    R_AGT_Stop(&g_timer1_ctrl);
    R_AGT_Close(&g_timer1_ctrl);
}