#include "time_measurement.h"
#include <chrono>
#include <cstdlib>
#include <cmath>


double compute_mean(const std::vector<double>& measurements) {
    // Summera alla mätvärden och dela på antalet för att få medelvärdet
    double sum = 0.0;
    for (double measurement : measurements) {
        sum += measurement;
    }
    return sum / measurements.size();
}

double compute_std_dev(const std::vector<double>& measurements) {
    double mean = compute_mean(measurements);           //Beräkna medelvärdet
    double variance = 0.0;

    // Summera kvadrerade avvikelser från medelvärdet
    for (double measurement : measurements) {
        double diff = measurement - mean;
        variance += diff * diff;            //snabbare än pow(diff, 2) eftersom det inte involverar en funktionsanrop 
    }

    // Dela med N-1 istället för N — Bessels korrektion för stickprov
    variance /= (measurements.size() - 1);

    // Standardavvikelsen är roten ur variansen
    return sqrt(variance);
}