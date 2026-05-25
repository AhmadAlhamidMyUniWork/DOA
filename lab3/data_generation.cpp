#include "data_generation.h"

// Genererar alla primtal upp till upper_limit med hjälp av Eratosthenes algoritmen.
std::vector<int> generate_primes(int upper_limit) {
    if (upper_limit < 2) return {};

    // Alla index antas vara primtal 
    std::vector<bool> is_prime(upper_limit + 1, true);
    // 0 och 1 är per definition inte primtal
    is_prime[0] = false;
    is_prime[1] = false;

    int current_prime = 2;
    // Räcker att sikta upp till N/2 eftersom multiplar däröver redan markerats
    while (current_prime < upper_limit / 2) {
        // Börja markera från 2*i eftersom mindre multiplar redan hanterats
        int divisor = current_prime * 2;
        // Markera alla multiplar av current_prime som icke-primtal
        while (divisor <= upper_limit) {
            is_prime[divisor] = false;
            divisor += current_prime;
        }
        current_prime++;
        // Hoppa över redan markerade tal för att hitta nästa primtal
        while (current_prime <= upper_limit && !is_prime[current_prime]) {
            current_prime++;
        }
    }

    // Skapa en vektor för att lagra primtalen
    // loopa igenom och lägg till index där värdet är true
    std::vector<int> primes;
    for (int index = 2; index <= upper_limit; ++index) {
        if (is_prime[index]) {
            primes.push_back(index);
        }
    }

    return primes;
}