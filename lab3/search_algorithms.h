#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H
#include <vector>

// Hashtable nod för separate chaining
struct hash_node {
    int data;
    hash_node* next;
};

// Sök efter ett värde i hashtabellen
bool hashtable_search(const std::vector<hash_node*>& hashtable, int search_value, int table_size);
// Frigör minnet allokerat för hashtabellen
void free_hashtable(std::vector<hash_node*>& hashtable);


// Functor för hashtable sökning 
struct HashTableSearcher {
    const std::vector<hash_node*>& table;
    int table_size;
    // Överlagra operator() så att vi kan använda detta som en sökfunktion i measure_search_times
    bool operator()(const std::vector<hash_node*>&, int search_value) const {
        return hashtable_search(table, search_value, table_size);
    }
};

// Deklarationer av sökalgoritmer
bool linear_search(const std::vector<int>& data, int search_value);
bool binary_search(const std::vector<int>& data, int search_value);

// Bygg ett balanserat binärt sökträd från en sorterad lista av primtal
void build_bst(
    const std::vector<int>& primes,
    std::vector<int>& bst,
    int bst_index,
    int prime_left,
    int prime_right
);

// Wrapper function för att skapa sökträdet från listan av primtal
std::vector<int> create_bst(const std::vector<int>& primes);

// Sök efter ett värde i ett binärt sökträd 
bool bst_search(const std::vector<int>& bst, int search_value);

// Bygg en hashtabell från sorterade primtal med separate chaining
std::vector<hash_node*> build_hashtable(
    const std::vector<int>& primes,
    int table_size
);


#endif // SEARCH_ALGORITHMS_H