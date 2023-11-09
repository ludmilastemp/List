#include <stdio.h>

#include "STL_list.h"
#include "STL_list_struct.h"

#include "STL_list_standard.h"
#include "STL_graphviz.h"

    //{}o,o{}
    //   |
    //   |
    //   |
    //   ^

int main ()
{

    Node node0 = { 10 };
    node0.next = &node0;
    node0.prev = &node0;

    Node* node1 = ListStandardInsert (&node0, 15);
    Node* node2 = ListStandardInsert (node1,  25);
    Node* node3 = ListStandardInsert (&node0, 20);

    node3 = ListStandardDelete (node3);
    node1 = ListStandardDelete (node1);

    printf ("node0\n");
        printf ("\tdata = %d\n", node0.data);
        printf ("\tptr  = %d\n", &node0);
        printf ("\tnext = %d\n", node0.next);
        printf ("\tprev = %d\n", node0.prev);

    printf ("node1\n");
        printf ("\tptr  = %d\n", node1);

    printf ("node2\n");
        printf ("\tdata = %d\n", node2->data);
        printf ("\tptr  = %d\n", node2);
        printf ("\tnext = %d\n", node2->next);
        printf ("\tprev = %d\n", node2->prev);

    printf ("node3\n");
        printf ("\tptr  = %d\n", node3);

    return 0;

    struct List list = { };
    ListStructCtor (&list);

    ListStructDump (&list);
    ListStructVerificator (&list);

    printf ("10 -- %d\n", ListInsert (&list, 0, 10));
    ListStructVerificator (&list);

    printf ("20 -- %d\n", ListInsert (&list, 1, 20));
    ListStructVerificator (&list);

    printf ("15 -- %d\n", ListInsert (&list, 1, 15));
    ListStructVerificator (&list);

    ListDelete (&list, 2);
    ListDelete (&list, 1);

    printf ("55 -- %d\n", ListInsert (&list, 0, 55));
    ListStructVerificator (&list);

    ListStructVerificator (&list);
    ListStructDump (&list);

    STL_Graphviz (&list);

    ListStructDtor (&list);

    printf ("END!");
}
