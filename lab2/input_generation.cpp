#include "input_generation.h"
#include <vector>
#include <algorithm>

std::vector<int> generate_increasing(int n) {
    std::vector<int> seq;
    for (int i = 0; i < n; i++) {
        seq.push_back(i);
    }
    return seq;
}

std::vector<int> generate_decreasing(int n) {
    std::vector<int> seq;
    for (int i = n - 1; i >= 0; i--) {
        seq.push_back(i);
    }
    return seq;
}

std::vector<int> generate_random(int n) {
    std::vector<int> seq;
    for (int i = 0; i < n; i++) {
        seq.push_back(rand() % n);
    }
    return seq;
}

std::vector<int> generate_constant(int n) {
    std::vector<int> seq(n, 1); // Alla element är 1
    return seq;
}
  