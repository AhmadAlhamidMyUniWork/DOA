#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
/**
 * Sort using quick sort algorithm
 * @param begin Pointer to the beginning of the sequence
 * @param end Pointer to the end of the sequence
 *
 */
//selection sort
void selection_sort(int*, int*) {
}

/**
 * @param begin first element of the sequence, begin, end cannot be empty container
 * @param end one past the last element of the sequence
 * @param begin Pointer to the beginning of the array
 * @param end Pointer to the end of the array
 */
int* find_min(int*, int*);

int* find_min(int* begin, int* end) {
    auto min = begin;
    for(auto it = begin; it != end; ++it){
        if(*it < *min){
            min = it;
        }
    }
    return min;
}

/**
 * För varje element
 * 
 */
void selection_sort(int* begin, int* end) {
    for(int* it = begin; it !=end - 1; ++it){
        auto min = find_min(it, end);
        std::swap(*it, *min);
    }
}

std::vector<std::vector<int>> build_square(size_t N){
    std::vector<std::vector<int>> sq(N);
    for(auto& vec : sq){
        for(auto& e : vec){
            e = rand() % N;
        }
    }
    return sq;
}

template<class FwdIt, class Compare = std::less<>>
void insertion_sort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
    for (auto it = first; it != last; ++it) {
        auto const insertion = std::upper_bound(first, it, *it, cmp);
        std::rotate(insertion, it, std::next(it)); 
        assert(std::is_sorted(first, std::next(it), cmp));
    }
}
const int REPEAT = 100000;

int main(int argc, char** argv[]) {
    const int SIZE = 16;
    int data[] = {8, 3, 5, 2, 856, 23123, 12, 15, 98, 2253, 123, 4321, 123135, 12356, 876, 431,};
    std::vector<int> original_data(data, data + SIZE);
    auto od_it = original_data.begin();
    auto od_begin = od_it;
    auto od_end = original_data.end();
    auto elements = [&od_it, &od_begin, &od_end] (){
    // 1. Kontrollera om vi nått slutet → återställ
    if(od_it == od_end){
        od_it = od_begin;
    }
    // 2. Spara värdet
    auto current = *od_it;
    // 3. Flytta framåt
    ++od_it;
    // 4. Returnera värdet
    return current;
};
    std::vector<int> repeated_data(REPEAT * SIZE);
    std::generate(repeated_data.begin(), repeated_data.end(), elements); 
    auto r_it = &(*repeated_data.begin());

    
    auto start = std::chrono::high_resolution_clock::now();
    for(auto count = 0; count < REPEAT; ++count){
        selection_sort(r_it, r_it + SIZE);
        r_it += SIZE;
    }
    auto finished = std::chrono::high_resolution_clock::now();
    

    auto  elapsed_time = finished - start;
    while(elapsed_time < 1s){
        selection_sort(r_it, r_it + SIZE);
        r_it += SIZE;
        elapsed_time = finished - start;
    }

    std::chrono::milliseconds time = finished - start;
    std::cout << "Selection sort time: " << time.count() << "ms" << std::endl;

    return 0;
}