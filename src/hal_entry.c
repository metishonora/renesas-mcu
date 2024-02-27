#include "stdlib.h"
#include "hal_data.h"
#include "elevator.h"
#include "uart.h"
#include "gpio.h"
#include "fnd.h"
#include "agt.h"
#include "button.h"
#include "node.h"
#include "motor.h"
#include "sensor.h"
#include "sound.h"
#include "can.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
void handle_control(void);
FSP_CPP_FOOTER

struct elevator *elevator;
struct motor* motor;

/* 1. UART protocol */

enum STAGE {
    WAIT = -1,
    RCV_CLASS,
    RCV_SIZE,
    RCV_DATA
} uart_stage = WAIT;

void uartIRQ_callback(uart_callback_args_t *p_args) {
    if (p_args->event != UART_EVENT_RX_CHAR) return;

    uint32_t input = p_args->data;
    if (uart_stage == WAIT) {
        if (input == STX) {  // start receiving
            CLEAR_NODE();
            ++uart_stage;
        }
    } else {
        if (input == ETX) {  // stop receiving
            uart_stage = WAIT;
            handle_control();
        } else {
            NODE(uart_stage++) = (uint8_t)input;
        }
    }
}

void handle_control(void) {
    switch (node.FS) {
        case FS_FIRST: enqueue(elevator, 0); break;
        case FS_SECOND: enqueue(elevator, 1); break;
        case FS_THIRD: enqueue(elevator, 2); break;
        default: break;
    }
    if (!elevator->motoring) {
        switch (node.DC) {
            case DC_OPEN: {
                if (elevator->door_state > 0) {  // already open
                    elevator->door_state += 3;
                } else {
                    door_open(elevator);
                }
                break;
            }
            case DC_CLOSE: {
                door_close(elevator);
                break;
            }
            default: break;
        }
    }
    if (node.ES) start_emergency(elevator);
}

/* 2. AGT Timer */

// AGT0: 500ms
// AGT1: 200ms

volatile int count_1s = 0;  // 0 to 2

// 500ms timer interrupt
void AGT0_Interrupt(timer_callback_args_t *p_args) {
    FSP_PARAMETER_NOT_USED(p_args);

    toggle_gpio(1);
    if (elevator->emergency) {
        count_1s = 0;
        door_close(elevator);
    }
    if (elevator->door_state > 0) {
        ++count_1s;
        if (count_1s >= 2) {
            count_1s = 0;
            elevator->door_state--;
            if (!elevator->door_state) {
                door_close(elevator);
            }
        }
    }
}

#define __2MS 0x3A980
volatile int count_3s = -1;  // 0 to 15

// 200ms timer interrupt
void AGT1_Interrupt(timer_callback_args_t *p_args) {
    FSP_PARAMETER_NOT_USED(p_args);

    if (elevator->emergency) toggle_gpio(3);
    else if (!elevator->door_state) {
        if (elevator->q_size) {  // request가 존재하면
            volatile uint16_t resistor = read_resistor();
            set_motor_speed(motor, (unsigned long) (resistor * 50 / 10000 + 50));

            _Bool done;
            ++count_3s;

            if (count_3s == 15) {  // 층 하나 이동하기
                done = move(elevator);
                count_3s = -1;
                if (done) {         // 도착
                    stop_moving(elevator);
                    init_fnd();
                    play_sound(SOUND_ARRIVAL);
                    R_BSP_SoftwareDelay(2, BSP_DELAY_UNITS_SECONDS);
                    door_open(elevator);
                    return;
                }
            }

            // 처음 움직이거나, 층 이동했는데 계속 움직일 경우
            if (!count_3s || (count_3s == -1 && !done)) {
                start_moving(elevator, motor);
            }
        }
        rotate_fnd();
    }
}

/* 3. Switch */

enum SWITCHES {
    SW_1FLR = FIRST_BUTTON,
    SW_2FLR,
    SW_3FLR,
    SW_CLEAR
};

void buttonIRQ_callback(external_irq_callback_args_t *p_args) {
    uint32_t ch = p_args->channel;
    int floor = (int) (ch - FIRST_BUTTON);

    switch (ch) {
        case SW_1FLR:
        case SW_2FLR:
        case SW_3FLR: {
            enqueue(elevator, floor);
            break;
        }
        case SW_CLEAR: {
            stop_emergency(elevator);
            break;
        }
    }
}

/* 4. CAN */

void can_callback(can_callback_args_t *p_args) {
    FSP_PARAMETER_NOT_USED(p_args);
}

void hal_entry(void) {
    elevator = init_elevator();
    motor = init_motor(__2MS);
    init_can();
    init_gpio();
    init_agt();
    init_uart();
    init_button_irq();
    init_resistor();

    toggle_gpio(0);
    start_agt0();
    start_agt1();

    set_fnd(1, elevator->cur_floor + 1);
    set_fnd(2, elevator->goal_floor + 1);
    send_can(CAN_START, 0);

    for (;;) {
        display_fnd(elevator->motoring);
    }

#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

void R_BSP_WarmStart(bsp_warm_start_event_t event) {
    if (BSP_WARM_START_RESET == event) {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        R_FACI_LP->DFLCTL = 1U;

#endif
    }

    if (BSP_WARM_START_POST_C == event) {
        R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable();

BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable() {}
#endif
