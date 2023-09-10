#include "mpc.h"
#include <stdio.h>

int main()
{
    char input[1024];
    scanf("%1023[^\n]", input);

    ////

    mpc_parser_t *Reg = mpc_new("reg");
    mpc_parser_t *HexLit = mpc_new("hex");
    mpc_parser_t *MovLitReg = mpc_new("mov");
    mpc_parser_t *Instruction = mpc_new("ins");

    mpca_lang(MPCA_LANG_DEFAULT,
              "reg : \"ip\" | \"ac\" | \"sp\" | \"fp\" | /r[a-f]/ ;"
              "hex : /\\$[0-9a-fA-F]+/ ;"
              "mov : (\"MOV\" | \"mov\") <hex> ',' <reg> ;"
              "ins : /^/ <mov> /$/ ;",
              Reg, HexLit, MovLitReg, Instruction);

    mpc_result_t r;

    if (mpc_parse("input", input, Instruction, &r))
    {
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);
    }
    else
    {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    mpc_cleanup(4, Reg, HexLit, MovLitReg, Instruction);

    return 0;
}