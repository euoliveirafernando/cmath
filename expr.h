#ifndef _expr_h_
#define _expr_h_

#define lvalue(x)    x == var || x == function

extern token kind;

extern bool next_token(token t);
extern void expect(u_char c);

extern node * create_node(u_long op);
extern void create_edge(node * u, node * v);
extern node * create_value(void);
extern node * un(u_long op, node * u);
extern node * bin(node * u, u_long op, node * v);
extern node * ter(node * u, node * v, node * w);

extern node * table_lookup(table * t);

extern void error(const char * format, ...);

#endif