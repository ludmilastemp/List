#ifndef STL_list_standard_struct_
#define STL_list_standard_struct_

typedef int LIST_STANDARD_T;

struct Node
{
    LIST_STANDARD_T data;
    Node* next;
    Node* prev;
};

#endif /* STL_list_standard_struct_ */
