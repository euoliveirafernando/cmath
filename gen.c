#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "graph.h"
#include "opcode.h"
#include "gen.h"

static void opcode(node * xxx);

static void gen_character(char * character)
{
    byte("0x%x ", * character);
}

static void gen_constant(double * number)
{
    byte("%lf ", * number);
}

static void gen_variable(char * name)
{
    byte("$%s ", name);
}

static void gen_function(edge * x)
{
    byte("(");

    while (x != NULL) {
        opcode(x->v);
        
        if (x->v->pred != NULL) {
            x = x->v->pred;
            byte(", ");
        }
    }
    
    byte(")");
}

static void gen_op(char * name)
{
    byte("$%s := ", name);
}

static void opcode(node * x)
{
    if (x != NULL)
        switch (x->op) {
            case if_then:
            case or:
            case and:
            case equal:
            case not_equal:
            case less:
            case greater:
            case less_equal:
            case greater_equal:
            case add:
            case sub:
            case mul:
            case div:
            case per:
            case pow:
            case rad:
            case log:
                gen_op(x->data);
                opcode(x->pred->next->v);
                byte("%x", x->op);
                opcode(x->pred->v);
                byte("\n");
                break;
            case neg:
            case not:
            case det:
            case ln:
            case exp:
            case sqrt:
            case cbrt:
            case sin:
            case cos:
            case tan:
            case csc:
            case sec:
            case cot:
            case arcsin:
            case arccos:
            case arctan:
            case arccsc:
            case arcsec:
            case arccot:
                gen_op(x->data);
                byte("%x", x->op);
                opcode(x->pred->v);
                byte("\n");
                break;
            case ccharacter:
                gen_character(x->data);
                break;
            case constant:
                gen_constant(x->data);
                break;
            case var:
                gen_variable(x->data);
                break;
            case function:
                gen_function(x->pred);
                break;
        }
}

static void code(node * x)
{
    if (x != NULL) {
        code(x->next);
        opcode(x);
    }
}

void gen(graph * g)
{
    if (g != NULL)
        code(g->next);
}