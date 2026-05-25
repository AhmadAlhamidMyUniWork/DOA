#ifndef TIME_MEASUREMENT_H
#define TIME_MEASUREMENT_H

#include <vector>
#include <chrono>
#include <cstdlib>
#include <cmath>


// SearchFn är en funktion som tar (data, search_value)
// Template implementation
template<typename DataT, typename SearchFn>
std::vector<double> measure_search_times(
    SearchFn search_fn,
    const DataT& data,
    const std::vector<int>& primes,
    int num_measurements)
{
    std::vector<double> times;
    const auto measurement_period = std::chrono::milliseconds(100);

    for (int measurement = 0; measurement < num_measurements; ++measurement) {
        int num_searches = 0;
        int total_hits = 0;  // hindrar kompilatoroptimering

        auto start = std::chrono::steady_clock::now();

        // Sök under 100ms
        while (std::chrono::steady_clock::now() - start < measurement_period) {
            // Generera slumpmässigt sökvärde i rätt intervall
            int search_value = 2 + rand() % primes.back();
            
            // Resultatet används för att hindra kompilatoroptimering
            total_hits += search_fn(data, search_value);
            num_searches++;
        }

        // Beräkna tid per sökning
        auto elapsed = std::chrono::steady_clock::now() - start;
        auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
        double time_per_search = elapsed_us.count() / static_cast<double>(num_searches);
        
        times.push_back(time_per_search);
    }

    return times;
}

// Beräkna medelvärdet av en lista av mätvärden
double compute_mean(const std::vector<double>& measurements);

// Beräkna standardavvikelsen för mätvärden
double compute_std_dev(const std::vector<double>& measurements);

#endif // TIME_MEASUREMENT_H
