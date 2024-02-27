#ifndef FND_H_
#define FND_H_

extern int set_fnd(int, int);
extern void display_fnd(_Bool);
void __display_fnd(int dig, int val);
void __display_rotating(int dig);
extern void init_fnd(void);
extern void rotate_fnd(void);

#endif /* FND_H_ */
