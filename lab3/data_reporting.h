#ifndef DATA_REPORTING_H
#define DATA_REPORTING_H

#include <string>

// Spara resultaten i en fil i formatet: data_size, mean_time, std_dev, num_measurements
void save_results(
    const std::string& filename,
    int data_size,
    double mean_time,
    double std_dev,
    int num_measurements
);

#endif // DATA_REPORTING_H
