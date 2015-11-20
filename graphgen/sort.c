#include "sort.h"

id pivot(id *tab, id p, id r)
{
    id pivot = tab[p], i = p-1, j = r+1;
    id temp;
    while (1)
    {
        do j--;
        while (tab[j] > pivot);

        do i++;
        while (tab[i] < pivot);

        if (i < j)
        {
            temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
        else
            return j;
    }
}

void quickSort(id *tab, id p, id r)
{
    id q;
    if (p < r)
    {
        q = pivot(tab, p, r);
        quickSort(tab, p, q);
        quickSort(tab, q+1, r);
    }
}
