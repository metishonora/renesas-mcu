#ifndef MOTOR_H_
#define MOTOR_H_

enum DIR {
    DIR_CCW,
    DIR_CW
};

struct motor {
    long unsigned int cur_speed;
    unsigned int period;
    _Bool cur_direction;
};

extern struct motor *init_motor(unsigned int);
extern void start_motor(void);
extern void stop_motor(void);
extern void set_motor_speed(struct motor*, long unsigned int);
extern void set_motor_dir(struct motor*, enum DIR);

#endif /* MOTOR_H_ */
