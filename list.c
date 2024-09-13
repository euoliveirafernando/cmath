#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "type.h"
#include "token.h"
#include "graph.h"
#include "table.h"
#include "list.h"

list * create_list(void)
{
    list * x;

    x = cmath_alloc(sizeof (list));

    return x;
}

static void redeclared(node * u, node * v)
{
    if (strcmp(u->data, v->data) == 0)
        error("'%s' redeclared", u->data);
}

static bool declared(node * xxx)
{
    if (strcmp(xxx->data, identifier) == 0) {
        kind = lexan();
        return true;
    } else
        return false;
}

static void insert(node * u, node * v)
{
    redeclared(u, v);
    if (u->next == NULL)
        u->next = v;
    else
        insert(u->next, v);
}

void list_insert(list * x, node * xxx)
{
    if (x->next == NULL)
        x->next = xxx;
    else
        insert(x->next, xxx);
}

static node * lookup(node * xxx)
{
    if (xxx == NULL)
        return NULL;
    else {
        if (declared(xxx))
            return xxx;
        return lookup(xxx->next);
    }
}

node * list_lookup(list * x)
{
    if (x->next == NULL)
        return NULL;
    else
        return lookup(x->next);
}