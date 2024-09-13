cc = gcc
flags = -lm

cmath: cmath.c lexer.c parser.c expr.c ssa.c hash.c list.c gen.c out.c memory.c error.c
	$(cc) $^ -o $@ $(flags)

.PHONY: rm cmath