#include "timer.h"
#include <stdlib.h>

static inline bool tac_get_enable(Timer *timer) {
  return (timer->tac & (1 << 2));
}

static inline uint8_t tac_get_clock_select(Timer *timer) {
  return (timer->tac & 0x03);
}

void timer_init(Timer *timer) {
  timer->div = 0x18;
  timer->tima = 0x00;
  timer->tma = 0x00;
  timer->tac = 0xF8;
  timer->cycle_count = 0;
  timer->request_interrupt = false;
}

void timer_write(Timer *timer, TimerReg reg, uint8_t data) {
  switch (reg) {
  case (DIV):
    timer->div = 0x00;
    return;
  case (TIMA):
    timer->tima = data;
    return;
  case (TMA):
    timer->tma = data;
    return;
  case (TAC):
    timer->tac = data;
    return;
  }
}

uint8_t timer_read(Timer *timer, TimerReg reg) {
  switch (reg) {
  case (DIV):
    return timer->div;
  case (TIMA):
    return timer->tima;
  case (TMA):
    return timer->tma;
  case (TAC):
    return timer->tac;
  }
}

static inline void div_increment(Timer *timer) {
  if (timer->cycle_count >= 64) {
    timer->div++;
  }
}

static inline void counter_increment(Timer *timer) {
  if (!tac_get_enable(timer)) {
    return;
  }

  uint16_t timer_frequency = 0;

  switch (tac_get_clock_select(timer)) {
  case (0x00):
    timer_frequency = 256;
    break;
  case (0x01):
    timer_frequency = 4;
    break;
  case (0x02):
    timer_frequency = 16;
    break;
  case (0x03):
    timer_frequency = 64;
    break;
  }

  if (timer->cycle_count >= timer_frequency) {
    timer->cycle_count -= timer_frequency;
    if (timer->tima == 0xFF) {
      timer->tima = timer->tma;
      timer->request_interrupt = true;
      return;
    }
    timer->tima++;
  }
}

void timer_increment(Timer *timer) {
  div_increment(timer);
  counter_increment(timer);
}
