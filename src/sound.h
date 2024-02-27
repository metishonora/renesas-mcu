#ifndef SOUND_H_
#define SOUND_H_

enum SOUND {
    SOUND_ARRIVAL,
    SOUND_WARNING
};

// 44100 Hz
extern unsigned char arrival[155616];
extern unsigned char warning[284640];

extern void play_sound(int);

#endif