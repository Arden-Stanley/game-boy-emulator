#include "ld_test.h"
#include "../bus.h"
#include "../cpu.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static inline void print_regs(CPU *cpu) {
  printf("AF: 0x%04X\n", cpu->af);
  printf("BC: 0x%04X\n", cpu->bc);
  printf("DE: 0x%04X\n", cpu->de);
  printf("HL: 0x%04X\n", cpu->hl);
  printf("SP: 0x%04X\n", cpu->sp);
  printf("PC: 0x%04X\n\n", cpu->pc);
}

void ld_test() {
  CPU cpu = {.af = 0x0000,
             .bc = 0x0000,
             .de = 0x0000,
             .hl = 0x0000,
             .sp = 0xFFFE,
             .pc = 0x0100};
  printf("Initializing Registers\n");
  print_regs(&cpu);

  Bus bus;
  bus.rom = malloc(sizeof(uint8_t) * 0x8000);

  bus_write(&bus, 0x0100, 0x01);
  bus_write(&bus, 0x0101, 0x34);
  bus_write(&bus, 0x0102, 0x12);
  cpu_step(&cpu, &bus);
  printf("Running 0x01 Test: ld BC, n16\n");
  print_regs(&cpu);
  assert(cpu.bc == 0x1234);
  printf("Opcode 0x01 succeeded\n\n");

  cpu.a = 0x12;
  cpu.bc = 0x7000;
  bus_write(&bus, 0x103, 0x02);
  cpu_step(&cpu, &bus);
  printf("Running 0x02 Test: ld [BC], A\n");
  print_regs(&cpu);
  assert(bus_read8(&bus, 0x7000) == 0x12);
  printf("Opcode 0x02 succeeded\n\n");

  bus_write(&bus, 0x104, 0x06);
  bus_write(&bus, 0x105, 0x89);
  cpu_step(&cpu, &bus);
  printf("Running 0x06 Test: ld B, n8\n");
  print_regs(&cpu);
  assert(cpu.b == 0x89);
  printf("Opcode 0x06 succedded\n\n");

  cpu.sp = 0x1293;
  bus_write(&bus, 0x106, 0x08);
  bus_write(&bus, 0x107, 0x01);
  bus_write(&bus, 0x108, 0x70);
  cpu_step(&cpu, &bus);
  printf("Running 0x08 Test: ld B, n8\n");
  print_regs(&cpu);
  printf("Bus 0x7001-0x7002: 0x%X, 0x%X\n", bus_read8(&bus, 0x7001),
         bus_read8(&bus, 0x7002));
  assert(bus_read8(&bus, 0x7001) == 0x93);
  assert(bus_read8(&bus, 0x7002) == 0x12);
  printf("Opcode 0x08 succeeded\n\n");

  bus_write(&bus, 0x109, 0x0A);
  cpu.bc = 0x7003;
  bus_write(&bus, 0x7003, 0x15);
  cpu_step(&cpu, &bus);
  printf("Running 0x0A Test: ld A, [BC]\n");
  print_regs(&cpu);
  assert(cpu.a == 0x15);
  printf("Opcode 0x0A Succeeded\n\n");

  bus_write(&bus, 0x10A, 0x0E);
  bus_write(&bus, 0x10B, 0x67);
  cpu_step(&cpu, &bus);
  printf("Running 0x0E Test: ld C, n8\n");
  print_regs(&cpu);
  assert(cpu.c == 0x67);
  printf("Opcode 0x0E Succeeded\n\n");

  free(bus.rom);
}
