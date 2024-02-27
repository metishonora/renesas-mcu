#include "hal_data.h"
#include "gpio.h"

_Bool led_state[4];

void init_gpio(void) {
    R_PORT10->PDR  = 0x0700;
    R_PORT11->PDR  = 0x0001;
    R_PORT10->PODR = 0x0700;
    R_PORT11->PODR = 0x0001;
}

_Bool get_led_state(int dig) {
    return led_state[dig];
}

/**
 * Toggles a specific LED.
 *
 * @param place     which led to toggle. 0 to 3.
 */
void toggle_gpio(int place) {
    led_state[place] ^= 0x1;
    R_PORT10->PODR = (uint16_t)(!led_state[0] << 8 | !led_state[1] << 9 |
                                !led_state[2] << 10);
    R_PORT11->PODR = !led_state[3];
}
