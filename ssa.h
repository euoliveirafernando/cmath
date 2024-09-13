#ifndef _ssa_h_
#define _ssa_h_

extern FILE * input;
extern token kind;

extern char identifier[];
extern double number;
extern char * string;
extern char character;

extern u_long addr;

extern void get_next_token(void);

extern void * cmath_alloc(size_t size);

extern void error(const char * format, ...);

#endif