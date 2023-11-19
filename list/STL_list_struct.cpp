#include "STL_list_struct.h"

// objdump -t main.o   // для static const

static const int LIST_INITIAL_CAPACITY  = 4;      // hdr
static const int LIST_INITIAL_SIZE      = 0;
static const int LIST_EXPAND_MULTIPLIER = 2;

int ListStructCtor (List* list)
{
    list->capacity = LIST_INITIAL_CAPACITY;

    ListStructRealloc (list);

    list->size = LIST_INITIAL_SIZE;
    list->free = 1;

    for (int i = 0; i < list->capacity; ++i)
    {
        *(list->data + i) = List::DATA_POISON;
        *(list->prev + i) = List::PREV_POISON;
        *(list->next + i) = i + 1;
    }

    list->next[0] = 0;
    list->prev[0] = 0;
    list->next[list->capacity - 1] = 0;

    return 0;
}

int ListStructDtor (List* list)
{
    free (list->data);
    free (list->next);
    free (list->prev);

    list->data = nullptr;
    list->next = nullptr;
    list->prev = nullptr;

    list->capacity = 0;
    list->size = 0;
    list->free = 0;

    return 0;
}


#ifdef OTCHAILSA
// ZHopa ne smotri
// Vnizu tolko smert
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// Poslednie preduprezhdenie
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// ...
// Ia sdelal vse chto mog
#endif


#define ERROR(x) printf ("ERROR!!! " #x "\n")

int ListStructVerificator (List* list)
{
    if (list->capacity <= 0)
    {
        ERROR (INCORRECT_CAPACITY);
        return 1;
    }

    if (list->size < 0) ERROR (INCORRECT_SIZE);
    if (list->free < 0) ERROR (INCORRECT_FREE);

    for (int i = 0; i < list->capacity; i++)
    {
        if (list->next[i] >= list->capacity || list->next[i] < -1)
            ERROR (INCORRECT_NEXT_DATA);

        if (list->prev[i] >= list->capacity || list->prev[i] < -1)
            ERROR (INCORRECT_PREV_DATA);

        if (list->prev[i] != -1)
        {
            if (list->data[list->next[list->prev[i]]] != list->data[i])
                ERROR (NO_SYMMETRY);

            if (list->data[list->prev[list->next[i]]] != list->data[i])
                ERROR (NO_SYMMETRY);
        }
    }

    int index = list->next[0];
    for (int i = 0; i < list->size; i++)
    {
        if (list->prev[index] == List::PREV_POISON) ERROR (INCORRECT_PREV_DATA);

        index = list->next[index];
    }
    if (index != 0) ERROR (FOUND_CYCLE);

    index = list->free;
    for (int i = 0; i < list->capacity - list->size - 1; i++)
    {
        if (list->prev[index] != List::PREV_POISON) ERROR (INCORRECT_PREV_DATA);

        index = list->next[index];
    }
    if (index != 0) ERROR (FOUND_CYCLE);

    index = list->prev[0];
    for (int i = 0; i < list->size; i++)
    {
        if (index == -1) ERROR (INCORRECT_PREV_DATA);

        index = list->prev[index];
    }
    if (index != 0) ERROR (FOUND_CYCLE);

    return 0;
}

#undef ERROR

int ListStructDump (List* list)
{
    printf ("capacity = %d\n", list->capacity);
    printf ("size = %d\n", list->size);
    printf ("free = %d\n", list->free);

    printf ("     ");
    for (int i = 0; i < list->capacity; ++i)
    {
        printf ("%2d ", i);
    }
    printf ("\n");

    printf ("data ");
    for (int i = 0; i < list->capacity; ++i)
    {
        printf (LIST_DATA_PRINTF_SPECIFIER " ", list->data[i]);
    }
    printf ("\n");

    printf ("next ");
    for (int i = 0; i < list->capacity; ++i)
    {
        printf ("%2d ", list->next[i]);
    }
    printf ("\n");

    printf ("prev ");
    for (int i = 0; i < list->capacity; ++i)
    {
        printf ("%2d ", list->prev[i]);
    }
    printf ("\n");


    printf ("\n");

    return 0;
}

#define ERROR(x) printf ("ERROR!!! " #x "\n")

int ListStructRealloc (List *list)
{
    assert (list);

    list->capacity *= LIST_EXPAND_MULTIPLIER;

    list->data = (int*) realloc (list->data, list->capacity * sizeof (LIST_T));
    if (list->data == nullptr) ERROR (DATA_NULLPTR);
    assert (list->data); // err

    list->next = (int*) realloc (list->next, list->capacity * sizeof (int));
    if (list->next == nullptr) ERROR (NEXT_NULLPTR);
    assert (list->next);

    list->prev = (int*) realloc (list->prev, list->capacity * sizeof (int));
    if (list->prev == nullptr) ERROR (PREV_NULLPTR);
    assert (list->prev);

    for (int i = list->capacity / LIST_EXPAND_MULTIPLIER; i < list->capacity; ++i)
    {
        *(list->data + i) = List::DATA_POISON;
        *(list->prev + i) = List::PREV_POISON;
        *(list->next + i) = i + 1;
    }

    list->next[list->capacity - 1] = list->free;
    list->free = list->capacity / LIST_EXPAND_MULTIPLIER;

    return 0;
}
