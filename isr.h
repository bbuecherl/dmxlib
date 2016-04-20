#ifndef DMXLIB_ISR_H_
#define DMXLIB_ISR_H_

#include "Arduino.h"
#include <avr/interrupt.h>

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define ISR_ENABLE() TIMSK2 |= _BV(TOIE2)
#define ISR_DISABLE() TIMSK2 &= ~_BV(TOIE2)
#define ISR_FUNCTION() ISR(TIMER2_OVF_vect, ISR_NOBLOCK)
#elif defined(__AVR_ATmega32U4__)
#define ISR_ENABLE() TIMSK3 |= _BV(TOIE2)
#define ISR_DISABLE() TIMSK3 &= ~_BV(TOIE2)
#define ISR_FUNCTION() ISR(TIMER3_OVF_vect, ISR_NOBLOCK)
#elif defined(__AVR_ATmega8__)
#define ISR_ENABLE() TIMSK |= _BV(TOIE2)
#define ISR_DISABLE() TIMSK &= ~_BV(TOIE2)
#define ISR_FUNCTION() ISR(TIMER_OVF_vect, ISR_NOBLOCK)
#else
#error "DMXLib does not support this CPU"
#endif

#endif // DMXLIB_ISR_H_
