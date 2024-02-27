#include "hal_data.h"
#include "can.h"

struct st_can_frame frame = {
	.id_mode = CAN_ID_MODE_STANDARD,
	.type = CAN_FRAME_TYPE_DATA,
	.data_length_code = 8
};

const char* msg[N_CAN_MSG] = {
	"CAN OKEY",
	"Same t X",
	"MoveTo N",
	"ArriTo N",
	"DR Open ",
	"DR Close"
};

void init_can(void) {
	R_CAN_Open(&g_can0_ctrl, &g_can0_cfg);
}

void send_can(enum CAN type, int info) {
	for (int i = 0; i < 8; ++i) {
		frame.data[i] = (uint8_t) msg[type][i];
	}

	switch (type) {
		case CAN_START:{
			frame.id = 0;
			break;
		}
		case CAN_DUP: {
			frame.id = 0;
			frame.data[7] = (uint8_t) info + '0';
			break;
		}
		case CAN_START_MOTOR: {
			frame.id = 1;
			frame.data[7] = (uint8_t) info + '0';
			break;
		}
		case CAN_STOP_MOTOR: {
			frame.id = 2;
			frame.data[7] = (uint8_t) info + '0';
			break;
		}
		case CAN_OPEN_DOOR:
		case CAN_CLOSE_DOOR: {
			frame.id = 3;
			break;
		}
		default: break;
	}

    R_CAN_Write(&g_can0_ctrl, 0, &frame);
}