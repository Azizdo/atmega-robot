#define F_CPU 8000000UL
#ifndef SOUND_H
#define SOUND_H

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/pwm.h>
#include <timer.h>

const double noteDutyCycles[]={4.545, 4.290, 4.049, 3.822, 3.607, 3.405, 3.214, 3.033, 2.863, 2.702, 2.551, 2.407,
2.272, 2.145, 2.024, 1.911, 1.803, 1.702, 1.607, 1.516, 1.431, 1.351, 1.275, 1.203, 1.136, 1.072, 1.012, 0.955, 
0.901, 0.851, 0.803, 0.758, 0.715, 0.675, 0.637, 0.601, 0.568};

class Sound{
public:
    Sound();
    void initPwm(int note);
    void playSound(int note);
    void stopSound();

    ~Sound();

/*A/B : % tjr un pwm a 50%, on controle surtout la periode du signal
  peut importe la periode
  
  trouver un mode entre ctc et qui fait sort quon peut controler la periode*/


};

#endif