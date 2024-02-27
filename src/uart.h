#ifndef UART_H_
#define UART_H_

extern const uint8_t STX;
extern const uint8_t ETX;

extern void init_uart(void);
extern void transmit_stream(char*);

#endif /* UART_H_ */
