#include "STL_list_standard.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Node*
ListStandardInsert (Node* address, LIST_STANDARD_T value)
{
    assert (address);

    Node* node = (Node*) calloc (1, sizeof (Node));
    assert (node); // error

    node->data = value;

    node->prev = address;
    address->next->prev = node;

    node->next = address->next;
    address->next = node;

    return node;
}

Node*
ListStandardDelete (Node* address)
{
    assert (address);

    address->next->prev = address->prev;
    address->prev->next = address->next;

    free (address);

    return nullptr;
}
