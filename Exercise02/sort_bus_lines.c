#include "sort_bus_lines.h"
#include "stdbool.h"

/**
 * this function uses pointers, to
 * swap between their values
 * @param pa - pointer to the first value
 * @param pb - pointer to the second value
 */
void swap(BusLine *pa, BusLine *pb)
{
    BusLine temp = *pa;
    *pa = *pb;
    *pb = temp;
}

// See full documentation in header file
void bubble_sort (BusLine *start, BusLine *end){
    // I used bubble sort pseudo-code from DAST
    int loop = end - start;
    for (int i = 0; i <= loop-1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < loop-1; j++)
        {
            if ((start + j)->distance > (start + j+1)->distance)
            {
                swap((start+j), (start + j+1));
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
}

// See full documentation in header file
void quick_sort(BusLine *start, BusLine *end)
{
    if (end - start > 0)
    {
        BusLine * index = partition(start, end);
        quick_sort(start, index);
        quick_sort(index+1, end);
    }
}

// See full documentation in header file
BusLine *partition (BusLine *start, BusLine *end){
    int i = -1;
    int length = end - start;
    for (int j = 0; j < length-1; j++) {
        if((start+j)->duration <= (end-1)->duration)
        {
            i++;
            swap(start + i, start + j);
        }
    }
    swap(start + i + 1, end-1);
    return start + i + 1;
}