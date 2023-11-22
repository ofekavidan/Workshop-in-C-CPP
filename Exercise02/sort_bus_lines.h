#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
/**
 * given struct of BusLine.
 * line_number = line number of each line
 * distance = distance from the campus to the station
 * duration = duration time from the campus to the station
 */
typedef struct BusLine
{
    int line_number, distance, duration;
} BusLine;

/**
 * the classic algorithm of bubble sort
 * just as said on DAST, uses swap function
 * @param start - start of the BusLine array
 * @param end - end of the BusLine array
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * the classic algorithm of quick sort
 * just as said on DAST, uses partition function recursively
 * @param start - start of the BusLine array
 * @param end - end of the BusLine array
 */
void quick_sort (BusLine *start, BusLine *end);

/**
 * helper for the quick-sort function
 * every iteration parts the array to 2 parts,
 * all the bigger elements than the pointer and all the smaller/equal
 * @param start - start of the BusLine array
 * @param end - end of the BusLine array
 * @return the appropriate index of the pointer
 */
BusLine *partition (BusLine *start, BusLine *end);
#endif //EX2_REPO_SORTBUSLINES_H
