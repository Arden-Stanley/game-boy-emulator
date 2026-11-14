#ifndef TIMER_H
#define TIMER_H
#include <stdbool.h>
#include <stdint.h>

typedef struct Timer {
  uint8_t div;
  uint8_t tima;
  uint8_t tma;
  uint8_t tac;
  uint16_t cycle_count;
  bool request_interrupt;
} Timer;

typedef enum TimerReg { DIV, TIMA, TMA, TAC } TimerReg;

void timer_init(Timer *timer);
void timer_write(Timer *timer, TimerReg reg, uint8_t data);
uint8_t timer_read(Timer *timer, TimerReg reg);
void timer_increment(Timer *timer);

#endif
