#ifndef GPIO_H_
#define GPIO_H_

extern void init_gpio(void);
extern _Bool get_led_state(int dig);
extern void toggle_gpio(int);

#endif /* GPIO_H_ */
