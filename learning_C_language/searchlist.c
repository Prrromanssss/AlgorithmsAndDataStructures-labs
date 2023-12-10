#include <stdio.h>
#include "elem.h"


struct Elem *searchlist(struct Elem *list, int k)
{
    if(list == NULL) {
        return NULL;
    }
    while(list->tail != NULL) {
        if(list->tag == INTEGER && list->value.i == k) {
            return list;
        }
        list = list->tail;
    }

    if(list->tag == INTEGER && list->value.i == k) {
        return list;
    }
    return NULL;
}
