#include "STL_graphviz.h"

#include <assert.h>

//#define pr(...) fprintf(fp, __VA_ARGS__)


int  STL_Graphviz (const List* list)
{
#define pr(...) fprintf (fp, __VA_ARGS__)
    FILE* fp = fopen ("STL_graphviz_png.dot", "w");
    assert (fp);

    pr ("digraph STL\n{\n");

    pr ("rankdir = LR\n");
    pr ("graph [ splines = ortho, splines = true ]\n");
    pr ("node  [ shape = record, style = filled, fillcolor = \"#FFD0D0\", color = \"#FFA0A0\" ]\n");
    pr ("edge  [ arrowhead = none ]\n\n");

    pr ("f0 [fillcolor = \"#D0FFFF\", color = \"#A0FFFF\", label = \" index | value |{ prev | next } \" ]\n");

    int i = 0;
    for (i = 1; i < list->capacity; i++)
    {
        pr ("f%d [label = \" %d | %d | { %d | %d } \" ", i, i, list->data[i], list->prev[i], list->next[i]);
        if (list->prev[i] == -1) pr ("fillcolor = \"#E7FFE7\", color = \"#A0FFA0\" ");
        pr (" ]\n");
    }

    for (i = 0; i < list->capacity - 1; i++)
    {
        pr ("f%d->", i);
    }
    pr ("f%d [ weight = 1000, color = \"#FFFFFF\" ]\n", list->capacity - 1);

    pr ("\nedge [ arrowhead = none, color = \"#FFA0A0\", style = bold ]\n");
    i = list->next[0];
    pr ("f0:ne-> f%d:nw\n", i);
    while (i != 0)
    {
        pr ("f%d:ne-> ", i);
        i = list->next[i];
        pr ("f%d:nw\n", i);
    }

    pr ("\nedge [ arrowhead = none, color = \"#A0FFA0\", style = bold ]\n");
    i = list->free;
    pr ("f0:se-> f%d:sw\n", i);
    while (i != 0)
    {
        pr ("f%d:se-> ", i);
        i = list->next[i];
        pr ("f%d:sw\n", i);
    }

    pr ("\nfh [ fillcolor = \"#D0FFFF\", color = \"#FFA0A0\", label = \"head\" ]\n");
    pr ("fh:s -> f%d:n", list->next[0]);
    pr ("[ weight = 300, color = \"#D0FFFF\", style = bold ]\n");

    pr ("\nff [ fillcolor = \"#D0FFFF\", color = \"#A0FFA0\", label = \"free\" ]\n");
    pr ("ff:s -> f%d:n", list->free);
    pr ("[ weight = 300, color = \"#D0FFFF\", style = bold ]\n");

    pr ("\nfh -> ff [ weight = 1000, color = \"#FFFFFF\" ]\n");

    pr ("}\n");

    fclose (fp);

#undef pr
}

