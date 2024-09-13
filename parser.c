#include <stdlib.h>
#include <stdbool.h>
#include "type.h"
#include "token.h"
#include "graph.h"
#include "table.h"
#include "parser.h"

void get_next_token(void)
{
    kind = lexan();
}

bool next_token(token t)
{
    if (kind == t) {
        get_next_token();
        return true;
    } else if (kind == eof)
        error("unexpected end of file");
    else
        return false;
}

void expect(u_char c)
{
    if (!next_token(c))
        error("expected '%c'", c);
}

static node * parse(node * x, table * t)
{
    node * u;
    
    u = expr(x, t);
    expect(';');
    
    return u;
}

graph * load(char * name)
{
    graph * g;
    table * t;

    g = create_graph(name);
    t = create_table(NULL);

    filename = name;
    line_number = 1;

    get_next_char();

    kind = lexan();

    while (!next_token(eof))
        if (next_token(';'));
        else
            g->next = parse(g->next, t);
    
    return g;
}