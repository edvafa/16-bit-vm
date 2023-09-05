enum
{
    MOV_LIT_REG = 0x10,
    MOV_REG_REG,
    MOV_REG_MEM,
    MOV_MEM_REG,
    ADD_REG_REG,
    JMP_NOT_EQ,
    PSH_LIT = 0x17,
    PSH_REG,
    POP = 0x1A,
    CAL_LIT = 0x5E,
    CAL_REG,
    RET,
    HLT = 0xff
};