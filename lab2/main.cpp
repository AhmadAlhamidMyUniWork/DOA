#include "performance_measurement.h"
#include "input_generation.h"
#include "sorting_algorithms.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
    

// Wrapper för std::sort
void std_sort_wrapper(int* begin, int* end) {
    std::sort(begin, end);
}

struct algo {
    std::string title;
    std::string filename;
    void (*sort_fn)(int*, int*);            //Funktionspekare till själva sorteringsalgoritmen
    std::vector<int> (*generate_fn)(int);   //Funktionspekare till datagenereringsfunktionen
    std::vector<int> sizes;
};

std::vector<algo> algos = {
    { "Insertion + Random",   "insertion_random.csv",   insertion_sort, generate_random, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Insertion + Sorted",   "insertion_sorted.csv",   insertion_sort, generate_increasing, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Insertion + Reversed", "insertion_reversed.csv", insertion_sort, generate_decreasing, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Insertion + Constant", "insertion_constant.csv", insertion_sort, generate_constant, {1000, 2000, 4000, 6000, 8000, 10000} },

    { "Selection + Random",   "selection_random.csv",   selection_sort, generate_random, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Selection + Sorted",   "selection_sorted.csv",   selection_sort, generate_increasing, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Selection + Reversed", "selection_reversed.csv", selection_sort, generate_decreasing, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Selection + Constant", "selection_constant.csv", selection_sort, generate_constant, {1000, 2000, 4000, 6000, 8000, 10000} },

    { "Quicksort + Random",   "quicksort_random.csv",   quicksort, generate_random, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "Quicksort + Sorted",   "quicksort_sorted.csv",   quicksort, generate_increasing, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Quicksort + Reversed", "quicksort_reversed.csv", quicksort, generate_decreasing, {1000, 2000, 4000, 6000, 8000, 10000} },
    { "Quicksort + Constant", "quicksort_constant.csv", quicksort, generate_constant, {10000, 30000, 50000, 70000, 90000, 100000} },

    { "Median3 Quicksort + Random",   "median3_quicksort_random.csv",   quicksort_median3, generate_random, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "Median3 Quicksort + Sorted",   "median3_quicksort_sorted.csv",   quicksort_median3, generate_increasing, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "Median3 Quicksort + Reversed", "median3_quicksort_reversed.csv", quicksort_median3, generate_decreasing, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "Median3 Quicksort + Constant", "median3_quicksort_constant.csv", quicksort_median3, generate_constant, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "std::sort + Random",   "std_sort_random.csv",   std_sort_wrapper, generate_random, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "std::sort + Sorted",   "std_sort_sorted.csv",   std_sort_wrapper, generate_increasing, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "std::sort + Reversed", "std_sort_reversed.csv", std_sort_wrapper, generate_decreasing, {10000, 30000, 50000, 70000, 90000, 100000} },
    { "std::sort + Constant", "std_sort_constant.csv", std_sort_wrapper, generate_constant, {10000, 30000, 50000, 70000, 90000, 100000} }

};

int main() {
    srand(time(0));
    for (const auto& algorithm : algos) {
        std::cout << "Running: " << algorithm.title << std::endl;

        std::ofstream file(algorithm.filename);

        if (!file) {
            std::cerr << "Could not open file: "
                      << algorithm.filename << std::endl;
            continue;
        }

        // Header-rad
        file << "N,T[ms],Stdev[ms],Samples\n";

        for (int n : algorithm.sizes) {
            std::vector<int> data = algorithm.generate_fn(n);

            measure_result result =
                measure_statistics(algorithm.sort_fn, n, data);

            file << n << ","
                 << result.mean_ms << ","
                 << result.stdev_ms << ","
                 << result.samples << "\n";

            std::cout << "  N=" << n
                      << " done" << std::endl;
        }

        file.close();
    }

    std::cout << "All benchmarks completed." << std::endl;
    return 0;
}