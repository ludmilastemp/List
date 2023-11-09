#include "STL_list.h"

int
ListInsert (List* list, int index, LIST_T value)
{
    int insertIndex = list->free;
    list->free  = list->next[list->free];

    if (index > list->capacity)
    {
        ListStructRealloc (list);
    }

    list->data[insertIndex] = value;

    list->prev[insertIndex] = list->prev[list->next[index]];
    list->prev[list->next[index]] = insertIndex;

    list->next[insertIndex] = list->next[index];
    list->next[index] = insertIndex;

    list->size++;

    return insertIndex;
}

int
ListDelete (List* list, int index)
{
    list->data[index] = List::DATA_POISON;

    list->prev[list->next[index]] = list->prev[index];
    list->next[list->prev[index]] = list->next[index];

    list->prev[index] = List::PREV_POISON;
    list->next[index] = list->free;

    list->free = index;

    list->size--;

    return index;
}
