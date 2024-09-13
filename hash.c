#include <string.h>
#include "type.h"
#include "graph.h"
#include "opcode.h"
#include "table.h"
#include "hash.h"

#define max 2048

table * create_table(table * next)
{
    table * t;

    t = cmath_alloc(sizeof (table));

    t->hash = cmath_alloc(sizeof (list * [max]));

    for (int i = 0; i < max; i++)
        t->hash[i] = create_list();

    t->next = next;

    return t;
}

static u_long hash(char * name)
{
    size_t length;
    u_long value = 0;

    length = strlen(name);

    for (int i = 0; i < length; i++) {
        value <<= 8;
        value += name[i];
    }

    return value % max;
}

void table_insert(table * t, node * x)
{
    u_long value;
    
    value = hash(x->data);
    list_insert(t->hash[value], x);
}

node * lookup(table * t, u_long value)
{
    node * x;

    if (t == NULL)
        return NULL;
    else {
        x = list_lookup(t->hash[value]);

        if (x == NULL)
            return lookup(t->next, value);
        else
            return x;
    }
}

node * table_lookup(table * t)
{
    u_long value;
    node * x;
    
    value = hash(identifier);
    x = lookup(t, value);
    
    if (x == NULL) {
        x = create_node(var);
        x->data = identifier;
    }
    
    get_next_token();
    
    return x;
}