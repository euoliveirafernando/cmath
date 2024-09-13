#ifndef _parser_h_
#define _parser_h_

extern token kind;
extern const char * filename;
extern unsigned int line_number;

extern char get_next_char(void);
extern token lexan(void);

extern node * expr(node * x, table * t);

extern graph * create_graph(const char * file);

extern table * create_table(table * prev);

extern void error(const char * format, ...);

#endif