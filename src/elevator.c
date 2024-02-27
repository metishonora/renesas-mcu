#include "stdlib.h"
#include "hal_data.h"
#include "elevator.h"
#include "uart.h"
#include "sound.h"
#include "gpio.h"
#include "node.h"
#include "can.h"
#include "fnd.h"

extern void transmit_stream(char *);

struct elevator *init_elevator(void) {
    struct elevator *elevator = (struct elevator *)malloc(sizeof(struct elevator));
    elevator->cur_floor  = 0;
    elevator->goal_floor = 0;
    elevator->emergency  = 0;
    elevator->motoring   = 0;
    elevator->q_size     = 0;
	elevator->door_state = 0;

    struct request *dummy = (struct request *)malloc(sizeof(struct request));
    dummy->floor          = -1;
    dummy->next = dummy->prev = dummy;
    elevator->queue           = dummy;
    return elevator;
}

void enqueue(struct elevator *elevator, int floor) {
	if (elevator->emergency) return;
	if (elevator->q_size >= 10) return;
	if (elevator->queue->prev->floor == floor) {
		send_can(CAN_DUP, floor + 1);
		return;
	}
	if (elevator->q_size == 0 && elevator->cur_floor == floor) return;

	struct request *newrq = (struct request*)malloc(sizeof(struct request));
	newrq->floor = floor;
	newrq->next = elevator->queue;
	newrq->prev = elevator->queue->prev;

	elevator->queue->prev->next = newrq;
	elevator->queue->prev = newrq;

	(elevator->q_size)++;
}

void dequeue(struct elevator *elevator) {
	struct request *complete = elevator->queue->next;
	elevator->queue->next = complete->next;
	if (elevator->q_size == 1) elevator->queue->prev = elevator->queue;
	elevator->q_size--;
	free(complete);
}

void start_moving(struct elevator *elevator, struct motor *motor) {
	elevator->motoring = 1;
	if (elevator->goal_floor > elevator->cur_floor) set_motor_dir(motor, DIR_CW);
	else set_motor_dir(motor, DIR_CCW);
	elevator->goal_floor = elevator->queue->next->floor;
	send_can(CAN_START_MOTOR, elevator->goal_floor + 1);
	set_fnd(2, elevator->goal_floor + 1);
	start_motor();
}

void stop_moving(struct elevator *elevator) {
	elevator->motoring = 0;
	if (elevator->q_size > 0) dequeue(elevator);
	stop_motor();
}

/**
 * cur_floor 변화.
 * 도착하면 true 반환.
 */
_Bool move(struct elevator *elevator) {
	if (elevator->cur_floor < elevator->goal_floor) elevator->cur_floor++;
	else elevator->cur_floor--;

	send_can(CAN_STOP_MOTOR, elevator->cur_floor + 1);
	set_fnd(1, elevator->cur_floor + 1);

	if (elevator->cur_floor == elevator->goal_floor) return 1;
	else return 0;
}

void door_open(struct elevator *elevator) {
	elevator->door_state = 3;
	send_can(CAN_OPEN_DOOR, 0);
	transmit_stream("OPEN");
}

void door_close(struct elevator *elevator) {
	transmit_stream("CLOSE");
	send_can(CAN_CLOSE_DOOR, 0);
	elevator->door_state = 0;
}

void start_emergency(struct elevator *elevator) {
	elevator->emergency = 1;
	elevator->goal_floor = elevator->cur_floor;
	stop_moving(elevator);
	while (elevator->q_size > 0) dequeue(elevator);
	play_sound(SOUND_WARNING);
}

void stop_emergency(struct elevator *elevator) {
	if (get_led_state(3)) toggle_gpio(3);
	elevator->emergency = 0;
	transmit_stream("RESUME");
}
