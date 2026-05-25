#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H


/**
 * Hitta minsta elementet i en sekvens
 * @param begin Pointer till första elementet i sekvensen
 * @param end Pointer till en element efter sista elementet i sekvensen
 * @return Pointer till minsta elementet i sekvensen 
 */
int* find_min(int* begin, int* end);

/**
 * Selection sort
 * @param begin Pointer till första elementet i sekvensen
 * @param end Pointer till en element efter sista elementet i sekvensen
 */
void selection_sort(int* begin, int* end);

/**
 * Insertion sort
 * @param begin Pointer till första elementet i sekvensen
 * @param end Pointer till en element efter sista elementet i sekvensen
 */
void insertion_sort(int* begin, int* end);

/**
 * Partition array med pivot = högra element
 * @param begin Pointer till första elementet i sekvensen
 * @param end Pointer till en element efter sista elementet i sekvensen
 * @return Pointer to where pivot ended up
 */
int* partition(int* begin, int* end);

/**
 * Quicksort med pivot = högra element
 * @param begin Pointer till första elementet i sekvensen
 * @param end Pointer till en element efter sista elementet i sekvensen
 */
void quicksort(int* begin, int* end);

/**
 * Quicksort med pivot = median-of-three
 * @param begin Pointer till första elementet i sekvensen
 * @param end Pointer till en element efter sista elementet i sekvensen
 */
void quicksort_median3(int* begin, int* end);

#endif
