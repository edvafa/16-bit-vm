#include "mpc.h"
#include <stdio.h>

int main()
{
    char input[1024];
    scanf("%1023[^\n]", input);

    ////

    mpc_parser_t *cod = mpc_new("cod");
    mpc_parser_t *reg = mpc_new("reg");
    mpc_parser_t *hex = mpc_new("hex");
    mpc_parser_t *add = mpc_new("add");
    mpc_parser_t *var = mpc_new("var");

    mpc_parser_t *lit = mpc_new("lit");
    mpc_parser_t *exp = mpc_new("exp");
    mpc_parser_t *ops = mpc_new("ops");
    mpc_parser_t *opp = mpc_new("opp");

    // mpc_parser_t *lbl = mpc_new("lbl");
    mpc_parser_t *ins = mpc_new("ins");
    mpc_parser_t *pgm = mpc_new("pgm");

    mpca_lang(MPCA_LANG_DEFAULT,
              "cod : /[a-z][a-z][a-z]?/ ;"
              "reg : \"ip\" | \"ac\" | \"sp\" | \"fp\" | /r[a-z]/ ;"
              "hex : /\\$[0-9a-z]+/ ;"
              "add : /\\&[0-9a-z]+/ ;"
              "var : /\\![a-z]+/ ;"

              "lit : <reg> | <hex> | <add> | <var> ;"
              "exp : <lit> | '(' <exp> ')' | <ops> ;"
              "ops : <opp> (('+' | '-') <opp>)* ;"
              "opp : <exp> ('*' <exp>)* ;"

              "ins : <cod> (<exp> (',' <exp>)*)? ;"
              "pgm : <ins>* ;",

              cod, reg, hex, add, var, lit, exp, ops, opp, ins, pgm);

    mpc_result_t r;

    if (mpc_parse("input", input, pgm, &r))
    {
        mpc_ast_print(r.output);
        mpc_ast_delete(r.output);
    }
    else
    {
        mpc_err_print(r.error);
        mpc_err_delete(r.error);
    }

    mpc_cleanup(11, cod, reg, hex, add, var, lit, exp, ops, opp, ins, pgm);

    return 0;
}