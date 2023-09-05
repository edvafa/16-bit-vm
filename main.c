// https://www.youtube.com/watch?v=mamop8aqFNk&list=PLP29wDx6QmW5DdwpdwHCRJsEubS5NrQ9b&index=3

#include <stdint.h>
#include <stdio.h>

#include "instructions.h"

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

struct CPU
{
    uint8_t mem[MEM_SIZE];
    uint16_t reg[NUM_REG];
} cpu;

void init()
{
    cpu.reg[sp] = MEM_SIZE - 2;
    cpu.reg[fp] = MEM_SIZE - 2;
}

uint8_t fetch()
{
    const uint8_t ins = cpu.mem[cpu.reg[ip]++];
    return ins;
}

uint16_t fetch16()
{
    uint8_t hi = cpu.mem[cpu.reg[ip]++];
    uint8_t lo = cpu.mem[cpu.reg[ip]++];
    const uint16_t ins = (hi << 8) | lo;
    return ins;
}

uint8_t fetch_reg()
{
    return fetch() % NUM_REG;
    ;
}

void push(uint16_t val)
{
    cpu.mem[cpu.reg[sp]] = val >> 8;
    cpu.mem[cpu.reg[sp] + 1] = val;
    cpu.reg[sp] -= 2;
}

uint16_t pop()
{
    cpu.reg[sp] += 2;
    uint8_t hi = cpu.mem[cpu.reg[sp]];
    uint8_t lo = cpu.mem[cpu.reg[sp] + 1];
    return (hi << 8) | lo;
}

void execute(uint8_t ins)
{
    switch (ins)
    {
    case MOV_LIT_REG:
    {
        const uint16_t lit = fetch16();
        const uint8_t reg = fetch_reg();
        cpu.reg[reg] = lit;
        return;
    }
    case MOV_REG_REG:
    {
        const uint8_t reg_from = fetch_reg();
        const uint8_t reg_to = fetch_reg();
        const uint16_t val = cpu.reg[reg_from];
        cpu.reg[reg_to] = val;
        return;
    }
    case MOV_REG_MEM:
    {
        const uint8_t reg = fetch_reg();
        const uint16_t address = fetch16();
        cpu.mem[address] = cpu.reg[reg] >> 8;
        cpu.mem[address + 1] = cpu.reg[reg];
        return;
    }
    case MOV_MEM_REG:
    {
        const uint16_t address = fetch16();
        const uint8_t reg = fetch_reg();
        cpu.reg[reg] = (cpu.mem[address] << 8) | cpu.mem[address + 1];
        return;
    }
    case ADD_REG_REG:
    {
        const uint16_t v0 = cpu.reg[fetch()];
        const uint16_t v1 = cpu.reg[fetch()];
        cpu.reg[ac] = v0 + v1;
        return;
    }
    case JMP_NOT_EQ:
    {
        const uint16_t lit = fetch16();
        const uint16_t address = fetch16();
        if (lit != cpu.reg[ac])
            cpu.reg[ip] = address;
        return;
    }
    case PSH_LIT:
    {
        const uint16_t val = fetch16();
        push(val);
        return;
    }
    case PSH_REG:
    {
        const uint8_t reg = fetch_reg();
        push(cpu.reg[reg]);
        return;
    }
    case POP:
    {
        const uint8_t reg = fetch_reg();
        cpu.reg[reg] = pop();
        return;
    }
    }
}

void step()
{
    const uint8_t ins = fetch();
    execute(ins);
}

void debug()
{
    printf("ip: %4x\n", cpu.reg[ip]);
    printf("ac: %4x\n", cpu.reg[ac]);
    printf("sp: %4x\n", cpu.reg[sp]);
    printf("fp: %4x\n", cpu.reg[fp]);
    printf("rA: %4x\n", cpu.reg[rA]);
    printf("rB: %4x\n", cpu.reg[rB]);
    printf("rC: %4x\n", cpu.reg[rC]);
    printf("rD: %4x\n", cpu.reg[rD]);
    printf("rE: %4x\n", cpu.reg[rE]);
    printf("rF: %4x\n", cpu.reg[rF]);
}

void debug_show_mem(uint16_t address)
{
    printf("0x%04x: ", address);
    for (int i = 0; i < 8; i++)
    {
        printf("%02x ", cpu.mem[address + i]);
    }
    printf("\n");
}

int main()
{
    int i = 0;

    // cpu.mem[i++] = MOV_MEM_REG;
    // cpu.mem[i++] = 0x01;
    // cpu.mem[i++] = 0x00;
    // cpu.mem[i++] = rA;

    // cpu.mem[i++] = MOV_LIT_REG;
    // cpu.mem[i++] = 0x00;
    // cpu.mem[i++] = 0x01;
    // cpu.mem[i++] = rB;

    // cpu.mem[i++] = ADD_REG_REG;
    // cpu.mem[i++] = rA;
    // cpu.mem[i++] = rB;

    // cpu.mem[i++] = MOV_REG_MEM;
    // cpu.mem[i++] = ac;
    // cpu.mem[i++] = 0x01;
    // cpu.mem[i++] = 0x00;

    // cpu.mem[i++] = JMP_NOT_EQ;
    // cpu.mem[i++] = 0x00;
    // cpu.mem[i++] = 0x03;
    // cpu.mem[i++] = 0x00;
    // cpu.mem[i++] = 0x00;

    //////////////

    cpu.mem[i++] = MOV_LIT_REG;
    cpu.mem[i++] = 0x51;
    cpu.mem[i++] = 0x51;
    cpu.mem[i++] = rA;

    cpu.mem[i++] = MOV_LIT_REG;
    cpu.mem[i++] = 0x42;
    cpu.mem[i++] = 0x42;
    cpu.mem[i++] = rB;

    cpu.mem[i++] = PSH_REG;
    cpu.mem[i++] = rA;

    cpu.mem[i++] = PSH_REG;
    cpu.mem[i++] = rB;

    cpu.mem[i++] = POP;
    cpu.mem[i++] = rA;

    cpu.mem[i++] = POP;
    cpu.mem[i++] = rB;

    init();
    while (1)
    {
        debug();
        debug_show_mem(cpu.reg[ip]);
        debug_show_mem(0xffff - 7);
        step();
        while (getchar() != '\n')
            ;
    }

    return 0;
}