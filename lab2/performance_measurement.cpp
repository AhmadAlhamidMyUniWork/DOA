#include "performance_measurement.h"
#include "input_generation.h"
#include "sorting_algorithms.h"
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>

const int INTERVALS = 10;
const int SAMPLES = 10;

measure_result measure_statistics(
    void (*sort_fn)(int*, int*),
    int n,
    const std::vector<int>& data
) {
    
    std::vector<double> times;
    times.reserve(SAMPLES);

    // Kör measure flera gånger
    for (int i = 0; i < SAMPLES; ++i) {
        double time_ns = measure(sort_fn, n, data);
        double time_ms = time_ns / 1'000'000.0;
        times.push_back(time_ms);
    }

    // Beräkna medelvärde
    double sum = 0.0;
    for (double t : times) {
        sum += t;
    }

    double mean = sum / SAMPLES;

    // Beräkna standardavvikelse
    double variance_sum = 0.0;
    for (double t : times) {
        double diff = t - mean;
        variance_sum += diff * diff;
    }

    double stdev = std::sqrt(variance_sum / (SAMPLES - 1));

    return { mean, stdev, SAMPLES };
}

double measure(void (*sort)(int*, int*), int n, std::vector<int> data) {
    std::vector<int> repeated_data(INTERVALS * n);

    // Förbered data (ej mätning)
    for (int i = 0; i < INTERVALS; ++i) {
        std::copy(data.begin(), data.end(),
                  repeated_data.begin() + i * n);
    }

    // Mät endast sortering
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < INTERVALS; ++i) {
        sort(repeated_data.data() + i * n,
             repeated_data.data() + (i + 1) * n);
    }

    auto stop = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        stop - start).count() / static_cast<double>(INTERVALS);
}

