#include "fnd.h"

#include "hal_data.h"

const uint16_t HEX_LO[]    = { 0x0, 0x9, 0x4, 0x0, 0x9, 0x2, 0x2, 0x8,
                            0x0, 0x0, 0x8, 0x3, 0x6, 0x1, 0x6, 0xE };
const uint16_t HEX_HI[]    = { 0xC, 0xF, 0xA, 0xB, 0x9, 0x9, 0x8, 0xD,
                            0x8, 0x9, 0x8, 0x8, 0xC, 0xA, 0x8, 0x8 };
const uint16_t ROTATE_LO[] = { 0xE, 0xD, 0xB, 0x7, 0xF, 0xF };
const uint16_t ROTATE_HI[] = { 0xF, 0xF, 0xF, 0xF, 0xE, 0xD };
volatile int fnd_state[4]  = { 4, 0, 0, -1 };

/**
 * Make a specific FND to display a number.
 *
 * @param place     where to set, 0 to 3
 * @param val       what number to set, 0 to 15
 * @return          0 on success, negatives on failure
 */
int set_fnd(int place, int val) {
    if (val < 0 || val > 15) return -1;
    if (place < 0 || place > 3) return -2;
    fnd_state[place] = val;
    return 0;
}

void display_fnd(_Bool moving) {
    __display_fnd(1, fnd_state[1]);
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    __display_fnd(2, fnd_state[2]);
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    if (moving) {
        __display_rotating(0);
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
        __display_rotating(3);
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

void __display_fnd(int dig, int val) {
    R_IOPORT_PortWrite(&g_ioport_ctrl, BSP_IO_PORT_03, 0x20 << dig, 0x01E0);
    R_IOPORT_PortWrite(&g_ioport_ctrl, BSP_IO_PORT_06,
                       (ioport_size_t)(HEX_HI[val] << 11 | HEX_LO[val] << 4),
                       0x38F0);
}

void __display_rotating(int dig) {
    volatile int val = dig ? fnd_state[dig] : 5 - fnd_state[dig];
    R_IOPORT_PortWrite(&g_ioport_ctrl, BSP_IO_PORT_03, 0x20 << dig, 0x01E0);
    R_IOPORT_PortWrite(
        &g_ioport_ctrl, BSP_IO_PORT_06,
        (ioport_size_t)(ROTATE_HI[val] << 11 | ROTATE_LO[val] << 4), 0x38F0);
}

void init_fnd(void) {
    fnd_state[0] = 4;
    fnd_state[3] = -1;
}

void rotate_fnd(void) {
    fnd_state[0] = (fnd_state[0] + 1) % 6;
    fnd_state[3] = (fnd_state[3] + 1) % 6;
}