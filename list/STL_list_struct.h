#ifndef STL_list_struct_
#define STL_list_struct_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int LIST_T;

#define TOSTR(x) #x
#define LIST_DATA_PRINTF_SPECIFIER TOSTR(%2d)

struct List
{
    LIST_T* data;
    int* next;
    int* prev;

    int capacity;
    int size;
    int free;

    static const int DATA_POISON = 0;
    static const int PREV_POISON = -1;
};

enum ListError
{
    DATA_NULLPTR,
    NEXT_NULLPTR,
    PREV_NULLPTR,
    INCORRECT_CAPACITY,
    INCORRECT_SIZE,
    INCORRECT_FREE,
    INCORRECT_DATA_DATA,
    INCORRECT_NEXT_DATA,
    INCORRECT_PREV_DATA,
    FOUND_CYCLE,
    NO_SYMMETRY,
};

int ListStructCtor (List* list);

int ListStructDtor (List* list);

int ListStructVerificator (List* list);

int ListStructDump (List* list);

int ListStructRealloc (List *list);

#endif /* STL_list_struct_ */
