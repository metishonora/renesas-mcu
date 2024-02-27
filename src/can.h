#ifndef CAN_H_
#define CAN_H_

enum CAN {
	CAN_START,
	CAN_DUP,
	CAN_START_MOTOR,
	CAN_STOP_MOTOR,
	CAN_OPEN_DOOR,
	CAN_CLOSE_DOOR,
	N_CAN_MSG
};

extern void init_can(void);
extern void send_can(enum CAN, int);

#endif