#include <stdbool.h>
#include <stdint.h>

#include "cpu.h"
#include "instructions.h"
#include "map.h"

void init(CPU *cpu)
{
    for (int i = 0; i < NUM_REG; i++)
    {
        cpu->reg[i] = 0;
    }
    cpu->run = true;
    cpu->reg[sp] = 0xffff - 1;
    cpu->reg[fp] = 0xffff - 1;
}

uint8_t fetch(CPU *cpu)
{
    const uint8_t ins = cpu->mem[cpu->reg[ip]++];
    return ins;
}

uint16_t fetch16(CPU *cpu)
{
    uint8_t hi = cpu->mem[cpu->reg[ip]++];
    uint8_t lo = cpu->mem[cpu->reg[ip]++];
    const uint16_t ins = (hi << 8) | lo;
    return ins;
}

uint8_t fetch_reg(CPU *cpu)
{
    return fetch(cpu) % NUM_REG;
}

void push(CPU *cpu, uint16_t val)
{
    cpu->mem[cpu->reg[sp]] = val >> 8;
    cpu->mem[cpu->reg[sp] + 1] = val;
    cpu->reg[sp] -= 2;
    cpu->frame_size += 2;
}

uint16_t pop(CPU *cpu)
{
    cpu->reg[sp] += 2;
    cpu->frame_size -= 2;
    uint8_t hi = cpu->mem[cpu->reg[sp]];
    uint8_t lo = cpu->mem[cpu->reg[sp] + 1];
    return (hi << 8) | lo;
}

void push_state(CPU *cpu)
{
    push(cpu, cpu->reg[ip]);
    push(cpu, cpu->reg[rA]);
    push(cpu, cpu->reg[rB]);
    push(cpu, cpu->reg[rC]);
    push(cpu, cpu->reg[rD]);
    push(cpu, cpu->reg[rE]);
    push(cpu, cpu->reg[rF]);
    push(cpu, cpu->frame_size + 2);
    cpu->reg[fp] = cpu->reg[sp];
    cpu->frame_size = 0;
}

void pop_state(CPU *cpu)
{
    const uint16_t frame_address = cpu->reg[fp];
    cpu->reg[sp] = frame_address;

    cpu->frame_size = pop(cpu);
    cpu->reg[rF] = pop(cpu);
    cpu->reg[rE] = pop(cpu);
    cpu->reg[rD] = pop(cpu);
    cpu->reg[rC] = pop(cpu);
    cpu->reg[rB] = pop(cpu);
    cpu->reg[rA] = pop(cpu);
    cpu->reg[ip] = pop(cpu);

    const uint16_t n_arg = pop(cpu);
    for (uint16_t i = 0; i < n_arg; i++)
    {
        pop(cpu);
    }
    cpu->reg[fp] = frame_address + cpu->frame_size;
}

void execute(CPU *cpu, uint8_t ins)
{
    switch (ins)
    {
    case MOV_LIT_REG:
    {
        const uint16_t lit = fetch16(cpu);
        const uint8_t reg = fetch_reg(cpu);
        cpu->reg[reg] = lit;
        return;
    }
    case MOV_REG_REG:
    {
        const uint8_t reg_from = fetch_reg(cpu);
        const uint8_t reg_to = fetch_reg(cpu);
        const uint16_t val = cpu->reg[reg_from];
        cpu->reg[reg_to] = val;
        return;
    }
    case MOV_REG_MEM:
    {
        const uint8_t reg = fetch_reg(cpu);
        const uint16_t address = fetch16(cpu);
        // cpu->mem[address] = cpu->reg[reg] >> 8;
        // cpu->mem[address + 1] = cpu->reg[reg];
        set_uint16(cpu, address, cpu->reg[reg]);
        return;
    }
    case MOV_MEM_REG:
    {
        const uint16_t address = fetch16(cpu);
        const uint8_t reg = fetch_reg(cpu);
        // cpu->reg[reg] = (cpu->mem[address] << 8) | cpu->mem[address + 1];
        cpu->reg[reg] = get_uint16(cpu, address);
        return;
    }
    case ADD_REG_REG:
    {
        const uint16_t v0 = cpu->reg[fetch(cpu)];
        const uint16_t v1 = cpu->reg[fetch(cpu)];
        cpu->reg[ac] = v0 + v1;
        return;
    }
    case JMP_NOT_EQ:
    {
        const uint16_t lit = fetch16(cpu);
        const uint16_t address = fetch16(cpu);
        if (lit != cpu->reg[ac])
            cpu->reg[ip] = address;
        return;
    }
    case PSH_LIT:
    {
        const uint16_t val = fetch16(cpu);
        push(cpu, val);
        return;
    }
    case PSH_REG:
    {
        const uint8_t reg = fetch_reg(cpu);
        push(cpu, cpu->reg[reg]);
        return;
    }
    case POP:
    {
        const uint8_t reg = fetch_reg(cpu);
        cpu->reg[reg] = pop(cpu);
        return;
    }
    case CAL_LIT:
    {
        const uint16_t address = fetch16(cpu);
        push_state(cpu);
        cpu->reg[ip] = address;
        return;
    }
    case CAL_REG:
    {
        const uint8_t reg = fetch_reg(cpu);
        const uint16_t address = cpu->reg[reg];
        push_state(cpu);
        cpu->reg[ip] = address;
        return;
    }
    case RET:
    {
        pop_state(cpu);
        return;
    }
    case HLT:
    {
        cpu->run = false;
        return;
    }
    }
}

void step(CPU *cpu)
{
    const uint8_t ins = fetch(cpu);
    execute(cpu, ins);
}

void run(CPU *cpu)
{
    while (cpu->run)
        step(cpu);
}