#include "hal_data.h"
#include "stdlib.h"
#include "motor.h"

/**
 * Initialize the motor.
 * The initial value of {direction, speed} is {CCW, 50%}.
 *
 * @param period_       base period in HEX
 */
struct motor* init_motor(unsigned int period_) {
    struct motor* motor = (struct motor*)malloc(sizeof(struct motor));

    motor->cur_direction = DIR_CCW;
    motor->cur_speed     = 50;
    motor->period        = period_;

    R_MSTP->MSTPCRD_b.MSTPD5 = 0;
    R_GPT3->GTCR_b.MD        = 0;
    R_GPT3->GTCR_b.TPCS      = 0;
    R_GPT3->GTPR             = motor->period - 1;
    R_GPT3->GTCNT            = 0;
    R_GPT3->GTIOR_b.GTIOA    = 9;
    R_GPT3->GTIOR_b.OAE      = 1;
    R_GPT3->GTCCR[0]         = motor->period / 2;

    return motor;
}

/**
 * Turns on the motor and GPT timer.
 */
void start_motor(void) {
    R_GPT3->GTCR_b.CST = 1;
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_00, BSP_IO_LEVEL_HIGH);
}

/**
 * Turns off the motor and GPT timer.
 * Direction and speed values will be maintained until the next time the motor
 * is turned on.
 */
void stop_motor(void) {
    R_GPT3->GTCR_b.CST = 0;
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_00, BSP_IO_LEVEL_LOW);
}

/**
 * @param spd       speed to set in percentile(%), 0 to 100
 * The larger value means the higher speed.
 */
void set_motor_speed(struct motor* motor, long unsigned int spd) {
    if (spd > 100) return;
    if (motor->cur_direction == DIR_CCW) {
        R_GPT3->GTCCR[0] = motor->period * spd / 100;
    } else {
        R_GPT3->GTCCR[0] = motor->period * (100 - spd) / 100;
    }
    motor->cur_speed = spd;
}

/**
 * Changes the direction of the DC motor.
 * There is a slight delay to protect the equipment.
 * If the current direction and the direction to change are the same, the call
 * is ignored.
 *
 * @param dir       direction to set. DIR_CCW or DIR_CW
 */
void set_motor_dir(struct motor* motor, enum DIR dir) {
    long unsigned int prev_speed = motor->cur_speed;
    if (motor->cur_direction == dir) return;
    set_motor_speed(motor, 0);
    R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);
    motor->cur_direction = dir;
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_09_PIN_01, motor->cur_direction);
    set_motor_speed(motor, prev_speed);
}
