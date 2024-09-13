#ifndef _cmath_h_
#define _cmath_h_

extern FILE * output;

extern graph * load(char * name);

extern void gen(graph * g);

extern void error(const char * format, ...);

#endif