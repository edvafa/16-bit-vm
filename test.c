#include "cpu.h"
#include "instructions.h"

void write_test_to_mem(CPU *cpu)
{
    int i = 0;

    // cpu->mem[i++] = MOV_MEM_REG;
    // cpu->mem[i++] = 0x01;
    // cpu->mem[i++] = 0x00;
    // cpu->mem[i++] = rA;

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x00;
    // cpu->mem[i++] = 0x01;
    // cpu->mem[i++] = rB;

    // cpu->mem[i++] = ADD_REG_REG;
    // cpu->mem[i++] = rA;
    // cpu->mem[i++] = rB;

    // cpu->mem[i++] = MOV_REG_MEM;
    // cpu->mem[i++] = ac;
    // cpu->mem[i++] = 0x01;
    // cpu->mem[i++] = 0x00;

    // cpu->mem[i++] = JMP_NOT_EQ;
    // cpu->mem[i++] = 0x00;
    // cpu->mem[i++] = 0x03;
    // cpu->mem[i++] = 0x00;
    // cpu->mem[i++] = 0x00;

    //////////////

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x51;
    // cpu->mem[i++] = 0x51;
    // cpu->mem[i++] = rA;

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x42;
    // cpu->mem[i++] = 0x42;
    // cpu->mem[i++] = rB;

    // cpu->mem[i++] = PSH_REG;
    // cpu->mem[i++] = rA;

    // cpu->mem[i++] = PSH_REG;
    // cpu->mem[i++] = rB;

    // cpu->mem[i++] = POP;
    // cpu->mem[i++] = rA;

    // cpu->mem[i++] = POP;
    // cpu->mem[i++] = rB;

    ///////////

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x33;
    // cpu->mem[i++] = 0x33;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x22;
    // cpu->mem[i++] = 0x22;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x11;
    // cpu->mem[i++] = 0x11;

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x12;
    // cpu->mem[i++] = 0x34;
    // cpu->mem[i++] = rA;

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x56;
    // cpu->mem[i++] = 0x78;
    // cpu->mem[i++] = rD;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x00;
    // cpu->mem[i++] = 0x00;

    // cpu->mem[i++] = CAL_LIT;
    // cpu->mem[i++] = 0x30;
    // cpu->mem[i++] = 0x00;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x44;
    // cpu->mem[i++] = 0x44;

    // cpu->mem[i++] = HLT;

    // i = 0x3000;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x01;
    // cpu->mem[i++] = 0x02;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x03;
    // cpu->mem[i++] = 0x04;

    // cpu->mem[i++] = PSH_LIT;
    // cpu->mem[i++] = 0x05;
    // cpu->mem[i++] = 0x06;

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x07;
    // cpu->mem[i++] = 0x08;
    // cpu->mem[i++] = rA;

    // cpu->mem[i++] = MOV_LIT_REG;
    // cpu->mem[i++] = 0x09;
    // cpu->mem[i++] = 0x0a;
    // cpu->mem[i++] = rF;

    // cpu->mem[i++] = RET;

    /////////////

    cpu->mem[i++] = MOV_LIT_REG;
    cpu->mem[i++] = 0x00;
    cpu->mem[i++] = 'H';
    cpu->mem[i++] = rA;

    cpu->mem[i++] = MOV_REG_MEM;
    cpu->mem[i++] = rA;
    cpu->mem[i++] = 0x10;
    cpu->mem[i++] = 0x00;

    cpu->mem[i++] = MOV_LIT_REG;
    cpu->mem[i++] = 0x00;
    cpu->mem[i++] = 'e';
    cpu->mem[i++] = rA;

    cpu->mem[i++] = MOV_REG_MEM;
    cpu->mem[i++] = rA;
    cpu->mem[i++] = 0x10;
    cpu->mem[i++] = 0x11;

    cpu->mem[i++] = MOV_LIT_REG;
    cpu->mem[i++] = 0x00;
    cpu->mem[i++] = 'l';
    cpu->mem[i++] = rA;

    cpu->mem[i++] = MOV_REG_MEM;
    cpu->mem[i++] = rA;
    cpu->mem[i++] = 0x10;
    cpu->mem[i++] = 0x22;

    cpu->mem[i++] = MOV_LIT_REG;
    cpu->mem[i++] = 0x00;
    cpu->mem[i++] = 'l';
    cpu->mem[i++] = rA;

    cpu->mem[i++] = MOV_REG_MEM;
    cpu->mem[i++] = rA;
    cpu->mem[i++] = 0x10;
    cpu->mem[i++] = 0x33;

    cpu->mem[i++] = MOV_LIT_REG;
    cpu->mem[i++] = 0x00;
    cpu->mem[i++] = 'o';
    cpu->mem[i++] = rA;

    cpu->mem[i++] = MOV_REG_MEM;
    cpu->mem[i++] = rA;
    cpu->mem[i++] = 0x10;
    cpu->mem[i++] = 0x44;

    cpu->mem[i++] = HLT;
}