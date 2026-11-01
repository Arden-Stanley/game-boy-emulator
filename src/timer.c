#include "timer.h"
#include <stdlib.h>

static inline bool tac_get_enable(Timer *timer) {
  return (timer->tac & (1 << 2));
}

static inline uint8_t tac_get_clock_select(Timer *timer) {
  return (timer->tac & 0x03);
}

Timer *timer_create() {
  Timer *timer = malloc(sizeof(Timer));
  timer->div = 0x18;
  timer->tima = 0x00;
  timer->tma = 0x00;
  timer->tac = 0xF8;
  return timer;
}

void timer_destroy(Timer *timer) { free(timer); }

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

static inline void div_increment(Timer *timer, uint16_t cycles) {
  if (cycles >= 64) {
  }
}

static inline void counter_increment(Timer *timer, uint16_t *cycles) {
  if (!tac_get_enable(timer)) {
    return;
  }
  switch (tac_get_clock_select(timer)) {
  case (0x00):
    if (*cycles >= 256) {
      *cycles -= 256;
    }
    break;
  case (0x01):
    if (*cycles >= 4) {
      *cycles -= 4;
    }
    break;
  case (0x02):
    if (*cycles >= 16) {
      *cycles -= 16;
    }
    break;
  case (0x03):
    if (*cycles >= 64) {
      *cycles -= 64;
    }
    break;
  }
}

void timer_increment(Timer *timer, uint16_t cycles) {}
