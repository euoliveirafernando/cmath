#include <stdlib.h>
#include <stdbool.h>
#include "type.h"
#include "token.h"
#include "graph.h"
#include "opcode.h"
#include "table.h"
#include "expr.h"

static node * assign(node * x, table * t);

static void expect_lvalue(u_long op)
{
    if (!(lvalue(op)))
        error("lvalue expected");
}

static node * call(node * x, table * t)
{
    node * u;
    
    if (next_token(')'))
        return NULL;
    
    do u = assign(x, t);
    while (next_token(','));
    
    expect(')');
    
    return u;
}

static node * bracket(node * x, table * t)
{
    node * u;
    
    if (next_token(']'))
        return NULL;
    
    u = assign(x, t);
    
    expect(']');
    
    return u;
}

static node * postfix(node * x, table * t)
{
    node * u;
    node * v;
    u_long op;
    
    u = table_lookup(t);
    while (post_expr(kind)) {
        if (next_token('(')) {
            op = function;
            v = call(x, t);
        } else if (next_token('[')) {
            op = subscript;
            v = bracket(x, t);
        } else if (next_token('.')) {
            op = access;
            v = table_lookup(t);
        }
        expect_lvalue(u->op);
        u = bin(u, op, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * primary(node * x, table * t)
{
    node * u;
    
    if (kind == token_ident)
        u = postfix(x, t);
    else if (next_token('(')) {
        u = assign(x, t);
        expect(')');
    } else if (next_token('|')) {
        u = assign(x, t);
        expect('|');
    } else if (primary_expr(kind))
        u = create_value();
    else
        error("expression expected");
    
    return u;
}

static node * matrix(node * x, table * t)
{
    node * u;
    
    if (next_token('[')) {
        do u = matrix(x, t);
        while (next_token(','));
        expect(']');
    } else
        u = primary(x, t);
    
    return u;
}

static node * tuple(node * x, table * t)
{
    node * u;
    
    if (next_token('{')) {
        do u = assign(x, t);
        while (next_token(','));
        expect('}');
    } else
        u = matrix(x, t);
    
    return u;
}

static node * unary(node * x, table * t)
{
    node * u;
    u_long op;
    
    if (next_token('+'))
        return unary(x, t);
    else if (next_token('-'))
        op = neg;
    else if (next_token('~'))
        op = not;
    else if (next_token(token_det))
        op = det;
    else if (next_token(token_ln))
        op = ln;
    else if (next_token(token_exp))
        op = exp;
    else if (next_token(token_sqrt))
        op = sqrt;
    else if (next_token(token_cbrt))
        op = cbrt;
    else if (next_token(token_sin))
        op = sin;
    else if (next_token(token_cos))
        op = cos;
    else if (next_token(token_tan))
        op = tan;
    else if (next_token(token_csc))
        op = csc;
    else if (next_token(token_sec))
        op = sec;
    else if (next_token(token_cot))
        op = cot;
    else if (next_token(token_arcsin))
        op = arcsin;
    else if (next_token(token_arccos))
        op = arccos;
    else if (next_token(token_arctan))
        op = arctan;
    else if (next_token(token_arccsc))
        op = arccsc;
    else if (next_token(token_arcsec))
        op = arcsec;
    else if (next_token(token_arccot))
        op = arccot;
    else
        return tuple(x, t);
    u = unary(x, t);
    u = un(op, u);
    create_edge(x, u);
    
    return u;
}

static node * pown(node * x, table * t)
{
    node * u;
    node * v;
    u_long op;
    
    u = unary(x, t);
    while (pow_expr(kind)) {
        if (next_token('^'))
            op = pow;
        else if (next_token(token_rad))
            op = rad;
        else if (next_token(token_log))
            op = log;
        v = unary(x, t);
        u = bin(u, op, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * prod(node * x, table * t)
{
    node * u;
    node * v;
    u_long op;
    
    u = pown(x, t);
    while (prod_expr(kind)) {
        if (next_token('*'))
            op = mul;
        else if (next_token('/'))
            op = div;
        else if (next_token('%'))
            op = per;
        v = pown(x, t);
        u = bin(u, op, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * sum(node * x, table * t)
{
    node * u;
    node * v;
    u_long op;
    
    u = prod(x, t);
    while (sum_expr(kind)) {
        if (next_token('+'))
            op = add;
        else if (next_token('-'))
            op = sub;
        v = prod(x, t);
        u = bin(u, op, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * rel(node * x, table * t)
{
    node * u;
    node * v;
    u_long op;
    
    u = sum(x, t);
    while (rel_expr(kind)) {
        if (next_token('<'))
            op = less;
        else if (next_token('>'))
            op = greater;
        else if (next_token(token_less_equal))
            op = less_equal;
        else if (next_token(token_greater_equal))
            op = greater_equal;
        v = sum(x, t);
        u = bin(u, op, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * rel_eq(node * x, table * t)
{
    node * u;
    node * v;
    u_long op;
    
    u = rel(x, t);
    while (rel_eq_expr(kind)) {
        if (next_token(token_equal))
            op = equal;
        else if (next_token(token_not_equal))
            op = not_equal;
        v = rel(x, t);
        u = bin(u, op, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * log_and(node * x, table * t)
{
    node * u;
    node * v;
    
    u = rel_eq(x, t);
    while (next_token(token_and)) {
        v = rel_eq(x, t);
        u = bin(u, and, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * log_or(node * x, table * t)
{
    node * u;
    node * v;
    
    u = log_and(x, t);
    while (next_token(token_or)) {
        v = log_and(x, t);
        u = bin(u, or, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * if_then_x(node * x, table * t)
{
    node * u;
    node * v;
    
    u = log_or(x, t);
    while (next_token(token_if_then)) {
        v = log_or(x, t);
        u = bin(u, if_then, v);
        create_edge(x, u);
    }
    
    return u;
}

static node * if_then_y(node * x, table * t)
{
    node * u;
    node * v;
    node * w;
    
    u = if_then_x(x, t);
    if (next_token('?')) {
        v = assign(x, t);
        expect(':');
        w = if_then_y(x, t);
        u = ter(u, v, w);
        create_edge(x, u);
    }
    
    return u;
}

static node * assign(node * x, table * t)
{
    node * u;
    node * v;
    
    u = if_then_y(x, t);
    if (next_token('=')) {
        expect_lvalue(u->op);
        v = assign(x, t);
        u = bin(u, store, v);
        create_edge(x, u);
    }
    
    return u;
}

node * expr(node * x, table * t)
{
    node * u;
    
    do u = assign(x, t);
    while (next_token(','));
    
    return u;
}