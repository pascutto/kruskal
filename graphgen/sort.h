#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include <stdlib.h>

typedef size_t id;

///Code taken from wikibooks and partially modified
id pivot(id *tab, id p, id r);
void quickSort(id *tableau, id p, id r);

#endif // SORT_H_INCLUDED
