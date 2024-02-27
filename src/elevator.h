#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include "motor.h"

struct request {
    int floor;
    struct request *next, *prev;
};

struct elevator {
    volatile int cur_floor;
    volatile int goal_floor;
    volatile int door_state;  // 남은 문 열림 시간
    volatile unsigned int emergency : 1;
    volatile unsigned int motoring : 1;
    struct request *queue;
    int q_size;
};

extern struct elevator *init_elevator(void);
extern void enqueue(struct elevator*, int);
extern void dequeue(struct elevator*);
extern _Bool move(struct elevator*);
extern void start_moving(struct elevator*, struct motor*);
extern void stop_moving(struct elevator*);
extern void door_open(struct elevator*);
extern void door_close(struct elevator*);
extern void start_emergency(struct elevator *elevator);
extern void stop_emergency(struct elevator *elevator);

#endif
