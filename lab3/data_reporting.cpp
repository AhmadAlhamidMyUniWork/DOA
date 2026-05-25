#include "data_reporting.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

void save_results(
    const std::string& filename,
    int data_size,
    double mean_time,
    double std_dev,
    int num_measurements
) {
    // Öppna fil i append-läge
    std::ofstream file(filename, std::ios::app);
    
    // Fail fast, kolla om filen öppnades
    if (!file.is_open()) {
        throw std::runtime_error("Kunde inte öppna fil: " + filename);
    }
    
    // Skriv kolumnerna tabbseparerade så filen enkelt kan läsas av plotverktyg
    file << data_size << "\t"
         << std::fixed << std::setprecision(4) << mean_time << "\t"
         << std::fixed << std::setprecision(4) << std_dev << "\t"
         << num_measurements << "\n";
    
    file.close();
}
