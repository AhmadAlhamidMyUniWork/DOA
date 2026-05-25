#include <iostream>
#include <vector>

template <typename It>
void iter_swap(It lhs, It rhs) {
    auto temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

template <typename It>
It min_element(It first, It last) {
    auto min_it = first;
    while (first != last) {
        if (*first < *min_it) {
            min_it = first;
        }
        first++;
    }
    return min_it;

}

template <typename It>
void selection_sort(It first, It last) {
    while (first != last) {
        It min_it = min_element(first, last);
        iter_swap(first, min_it);
        first++;
    }
}

int main() {
    std::vector<int> v(50'000);
    int i = 0;
    auto asc = [&i]() { return --i; };
    std::generate(v.begin(), v.end(), asc);
    selection_sort(v.begin(), v.end());
    for (auto e : v)
        std::cout << e << " , ";
    return 0;
}
