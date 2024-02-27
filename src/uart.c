#include "hal_data.h"
#include "uart.h"
#include "node.h"
#include "string.h"

const uint8_t STX = 0x02;
const uint8_t ETX = 0x03;

void init_uart(void) {
    R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
}

struct __attribute__((__packed__)) stream {
    uint8_t stx;
    uint8_t class;
    uint8_t data_size;
    uint8_t data[6];
};

struct stream stream = {
    .stx = STX,
    .class = CLASS_UPDATE,
};

/**
 * UART로 UPDATE 신호 보낼 때.
 * 다른 함수에서 호출해야 함.
 */
void transmit_stream(char *msg) {
    stream.data_size = (uint8_t) strlen(msg) + '0';

    size_t i;
    for (i = 0; i < strlen(msg); ++i) {
        stream.data[i] = (uint8_t) msg[i];
    }
    stream.data[i] = ETX;

    R_SCI_UART_Write(&g_uart0_ctrl, (uint8_t*) &stream, i + 4);
}