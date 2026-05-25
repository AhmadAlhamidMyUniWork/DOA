#include "sorting_algorithms.h"
#include <algorithm>
#include <iterator>
#include <cassert>


/**
 * Hitta minsta elementet i en sekvens
 */
int* find_min(int* begin, int* end) {
    auto min = begin;
    for(auto it = begin; it != end; ++it){
        if(*it < *min){ //Är det vi tiitar på mindre än det minsta vi hittills hittat?
            min = it; //Denna if sats styr komplexiteten i selection sort, den är O(n) eftersom vi måste titta på alla element för att hitta det minsta
        }
    }
    return min;
}

/**
 * Selection sort: hitta minimum och swappa för varje position
 */
void selection_sort(int* begin, int* end) {
    for(int* it = begin; it != end - 1; ++it){
        auto min = find_min(it, end);
        std::swap(*it, *min); //Här är algoritmen som bäst för när allt är ligger i ordning, så måste vi swappa alla element
    }
}

/**
 * Insertion sort: infoga varje element på rätt position i den sorterade delen O(log n) för att hitta rätt position och O(n) för att flytta element, så totalt O(n^2) i värsta fall,
 */
void insertion_sort(int* begin, int* end)
{
    //Loop genom varje element
    for (auto it = begin; it != end; ++it) { 
        auto const insertion = std::upper_bound(begin, it, *it);  //Hitta rätt position i sorterad delen (Binary search), returnerar en iterator som pekar på första elementet som är större än *it
        std::rotate(insertion, it, std::next(it));               //Flytta elementet till rätt position
        assert(std::is_sorted(begin, std::next(it)));           // Kolla att sorteringen är korrekt efter varje insättning
    }
}

/**
 * Partitionering: pivot = högra elementet
 */
int* partition(int* begin, int* end) {
    int* pivot_ptr = end - 1;      // Pivot = sista elementet
    int pivot = *pivot_ptr;
    
    int* first = begin;            // Letar från början
    int* last = end - 2;           // Letar innan pivot
    
    while(first <= last) {
        // flytta first åt höger tills vi hittar något som är >= pivot
        // first stannar på element >= pivot för hitta element på vänster som är större än pivot
        while(first <= last && *first < pivot) {
            ++first;
        }
        
        // flytta last åt vänster tills vi hittar något som är <= pivot
        while(first <= last && *last > pivot) {
            --last;
        }
        
        // Om de två pekarna inte har korsats, swappa (nu är stora element på höger, små på vänster)
        if(first <= last) {
            std::swap(*first, *last);
            ++first;
            --last;
        }
    }
    
    //  När loopen slutar, first pekar på en position där allt till vänster är < pivot och allt till höger är >= pivot
    std::swap(*first, *pivot_ptr);
    return first;
}

/**
 * Median-of-three: ordna så att minsta är på first, medianen på last, största på mid
 */
void median3(int* first, int* mid, int* last) {
    if(*first > *mid) {
        std::swap(*first, *mid);    // Nu är *first <= *mid
    }
    if(*first > *last) {
        std::swap(*first, *last);   // Nu är *first <= *last
    }
    if(*mid < *last) {
        std::swap(*mid, *last);     // Nu är *mid >= *last 
    }
}

/**
 * Quicksort med pivot = högra elementet
 */
void quicksort(int* begin, int* end) {
    if(begin >= end - 1) return;   // Basfall: 0 eller 1 element
    // Partitionera och få pivotens position efter partitionering
    int* pivot_pos = partition(begin, end);
    quicksort(begin, pivot_pos);        // Sortera vänster
    quicksort(pivot_pos + 1, end);      // Sortera höger
}

/**
 * Quicksort med pivot = median-of-three
 */
void quicksort_median3(int* begin, int* end) {
    // Basfall: 0, 1 eller 2 element
    if(end - begin < 3) {
        if(*begin > *(end - 1)) {
            std::swap(*begin, *(end - 1));
        }
        return;
    }
    
    // Steg 1: Beräkna median-of-three och ordna
    //Medianen är mycket bättre än helt random pivot för att få balanserad division
    int* mid = begin + (end - begin) / 2;
    median3(begin, mid, end - 1);
    
    // Steg 2: Partitionering börjar från begin + 1
    int* pivot_pos = partition(begin + 1, end);
    
    // Steg 3: Rekursiv sortering
    quicksort_median3(begin, pivot_pos);
    quicksort_median3(pivot_pos + 1, end);
}
