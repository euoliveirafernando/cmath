#ifndef _list_h_
#define _list_h_

extern token kind;

extern char identifier[];

extern token lexan(void);

extern void * cmath_alloc(size_t size);

extern void error(const char * format, ...);

#endif