#ifndef PERFORMANCE_MEASUREMENT_H
#define PERFORMANCE_MEASUREMENT_H

#include <vector>
struct measure_result {
    double mean_ms;
    double stdev_ms;
    int samples;
};

measure_result measure_statistics(
    void (*sort_fn)(int*, int*),   //Funktionspekare till sorteringsalgoritmen
    int n,                         //Storleken på datan 
    const std::vector<int>& data   //Den faktiska datan att sortera
);

/**
 * @brief Funktion som kör sorteringsalgoritmen en gång och returnerar tiden i nanosekundar.
 * @param samma som ovan
 * @return Tiden i nanosekundar det tog att sortera datan
 */
double measure(void (*sort_fn)(int*, int*), int n, std::vector<int> data);



#endif // PERFORMANCE_MEASUREMENT_H