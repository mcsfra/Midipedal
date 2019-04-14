/* 
 * File:   pedal.h
 * Author: marcus
 *
 * Created on 17. März 2014, 17:26
 */

#ifndef __PEDAL_H__
#define	__PEDAL_H__

extern void initPedal(void);
extern void probePedal(void);
extern void evalKeyStates(void);


extern unsigned char getState(unsigned char key);

extern unsigned char getOnState(unsigned char key);
extern unsigned char getOffState(unsigned char key);
extern unsigned int  getTimer(void);
extern unsigned char calculateVelocity(unsigned char key);

extern void debounce(unsigned char key, unsigned char nextState);

extern void handleTimerOverflow(void);

#endif	/* PEDAL_H */

