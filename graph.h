#ifndef _graph_h_
#define _graph_h_

struct edge;

struct node
{
    u_long op;
    u_long id;
    struct edge * pred;
    void * data;
    struct node * next;
};

typedef struct node node;

struct edge
{
    node * u;
    node * v;
    struct edge * next;
};

typedef struct edge edge;

struct list
{
    node * next;
};

typedef struct list list;

typedef list graph;

#endif