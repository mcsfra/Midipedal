/* 
 * File:   midi.h
 * Author: marcus
 *
 * Created on 17. März 2014, 17:28
 */

#ifndef __MIDI_H__
#define	__MIDI_H__

extern void initMidi(void);
extern void sendMidi(void);

extern void noteOn(unsigned char note, unsigned char velocity);
extern void noteOff(unsigned char note, unsigned char velocity);

extern unsigned char getMidiChannel(void);
extern unsigned char getTranspose(void);

extern void sendMidiStream(void);


#endif	/* MIDI_H */

