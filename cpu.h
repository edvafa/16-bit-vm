#ifndef _CPU
#define _CPU

#include <stdbool.h>
#include <stdint.h>

#define MEM_SIZE (1 << 16)

enum Registers
{
    ip, // instruction p
    ac, // accumulator
    sp, // stack p
    fp, // frame p
    rA,
    rB,
    rC,
    rD,
    rE,
    rF,
    NUM_REG
};

typedef struct CPU
{
    uint8_t mem[MEM_SIZE];
    uint16_t reg[NUM_REG];
    uint16_t frame_size;
    bool run;
} CPU;

#endif