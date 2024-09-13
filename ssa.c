#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "token.h"
#include "graph.h"
#include "opcode.h"
#include "ssa.h"

graph * create_graph(const char * name)
{
    graph * g;

    input = fopen(name, "r");

    if (input == NULL)
        error("%s: no such file", name);

    g = cmath_alloc(sizeof (graph));

    return g;
}

node * create_node(u_long op)
{
    node * x;
    
    x = cmath_alloc(sizeof (node));

    x->op = op;
    x->id = is_op(op) ? x->id++ : 0;
    
    return x;
}

void create_edge(node * u, node * v)
{
    edge * e;

    if (u == NULL || v == NULL)
        return;

    e = cmath_alloc(sizeof (edge));

    e->u = u;
    e->v = v;
    e->next = u->pred;
    u->pred = e;
}

node * create_value(void)
{
    node * x;
    
    x = create_node(val);
    switch (kind) {
        case token_integer_literal:
        case token_floating_point:
            x->data = cmath_alloc(sizeof (double));
            *(double *) x->data = number;
            get_next_token();
            return x;
        case token_character_constant:
        case token_string_literal:
            get_next_token();
            return x;
    }
}

node * un(u_long op, node * u)
{
    node * x;
    
    x = create_node(op);
    
    create_edge(x, u);
    
    return x;
}

node * bin(node * u, u_long op, node * v)
{
    node * x;
    
    x = create_node(op);
    
    create_edge(x, u);
    create_edge(x, v);
    
    return x;
}

node * ter(node * u, node * v, node * w)
{
    node * x;
    
    x = create_node(cond);
    
    create_edge(x, u);
    create_edge(x, v);
    create_edge(x, w);
    
    return x;
}