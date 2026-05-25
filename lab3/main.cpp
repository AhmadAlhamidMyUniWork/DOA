#include "data_generation.h"
#include "search_algorithms.h"
#include "time_measurement.h"
#include "data_reporting.h"
#include <iostream>

int main() {
    // Generera tillräckligt många primtal (behöver minst 8191)
    auto all_primes = generate_primes(100000);
    
    // Mät de fyra algoritmerna för olika datastorleken
    for (int data_size : {15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191}) {
        // Ta de första data_size primtalen
        std::vector<int> primes(all_primes.begin(), all_primes.begin() + data_size);
        
        std::cout << "Measuring with " << data_size << " primes..." << std::endl;
        
        // Linear search
        auto times_linear = measure_search_times(
            linear_search, primes, primes, 20
        );
        save_results("linear_search.data",
            data_size,
            compute_mean(times_linear),
            compute_std_dev(times_linear),
            20
        );
        
        // Binary search
        auto times_binary = measure_search_times(
            binary_search, primes, primes, 20
        );
        save_results("binary_search.data",
            data_size,
            compute_mean(times_binary),
            compute_std_dev(times_binary),
            20
        );
        
        // BST search
        auto bst = create_bst(primes);
        auto times_bst = measure_search_times(
            bst_search, bst, primes, 20
        );
        save_results("bst_search.data",
            data_size,
            compute_mean(times_bst),
            compute_std_dev(times_bst),
            20
        );
        
        // Hash table search — table_size skalerar med data_size
        int table_size = data_size * 2 + 3;
        auto table = build_hashtable(primes, table_size);
        auto times_hash = measure_search_times(
            HashTableSearcher{table, table_size},
            table, primes, 20
        );
        save_results("hashtable_search.data",
            data_size,
            compute_mean(times_hash),
            compute_std_dev(times_hash),
            20
        );
        free_hashtable(table);
    }
    
    std::cout << "Done! Results saved to .data files" << std::endl;
    return 0;
}
