#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "graph.h"
#include "cmath.h"

#define usage   "math compiler -- copyright (c) 2023\n"\
                "usage:       cmath <code> -b <byte>\n"

static void parse(int argc, char ** argv)
{
    graph * g;
    
    if (strcmp(argv[2], "-b") == 0) {
        output = fopen(argv[3], "w+");
        
        if (output == NULL)
            error("%s: unable to create file", argv[3]);
    } else
        error("missing bytecode name");
    
    g = load(argv[1]);
    
    gen(g);
}

int main(int argc, char ** argv)
{
    if (argc == 4)
        parse(argc, argv);
    else
        printf(usage);

    return 0;
}