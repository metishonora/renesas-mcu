#ifndef BUTTON_H_
#define BUTTON_H_

#define FIRST_BUTTON 11

extern void init_button_irq(void);
extern void enable_button_irq(void);
extern void disable_button_irq(void);

#endif /* BUTTON_H_ */
