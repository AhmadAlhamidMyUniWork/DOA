#include "search_algorithms.h"

bool linear_search(const std::vector<int>& data, int search_value) {
    // Gå igenom varje element ett i taget tills värdet hittas eller listan tar slut
    for (const int element : data) {
        if (element == search_value) {
            return true;                // Värdet hittades, returnera true
        }
    }
    return false;                       // Värdet hittades inte, returnera false
}

bool binary_search(const std::vector<int>& data, int search_value) {
    // Kontrollera först om listan är tom för att undvika onödiga beräkningar
    if (data.empty()) return false;

    int left_index = 0;
    int right_index = data.size() - 1;

    while (left_index <= right_index) {
        // Beräkna mitten
        int middle_index = left_index + (right_index - left_index) / 2;

        if (data[middle_index] == search_value) {
            return true;
        }
        else if (data[middle_index] < search_value) {
            // Värdet ligger i högra halvan, kasta bort vänster. Flutta fram vänsterindex
            left_index = middle_index + 1;
        }
        else {
            // Värdet ligger i vänstra halvan, kasta bort höger. Flutta bak högerindex
            right_index = middle_index - 1;
        }
    }

    return false;
}

void build_bst(
    const std::vector<int>& primes, // källdata
    std::vector<int>& bst,          // trädet vi bygger
    int bst_index,                  // var i trädet vi skriver just nu
    int prime_left,                 // vänster gräns i primes
    int prime_right                 // höger gräns i primes
) {
    // Basfall: om intervallet är tomt
    if (prime_left > prime_right) {
        return;
    }
    
    // Beräkna mittenelement
    int middle_index = prime_left + (prime_right - prime_left) / 2;
    
    // Sätt mittenelement som nod i trädet
    bst[bst_index] = primes[middle_index];
    
    // Rekursivt bygg vänster delträd, vänster barn av bst_index finns på 2*bst_index + 1
    build_bst(primes, bst, 2 * bst_index + 1, prime_left, middle_index - 1);
    
    // Rekursivt bygg höger delträd, höger barn av bst_index finns på 2*bst_index + 2
    build_bst(primes, bst, 2 * bst_index + 2, middle_index + 1, prime_right);
}

// Wrapper-funktion för att skapa sökträdet från listan av primtal
std::vector<int> create_bst(const std::vector<int>& primes) {
    // primes.size() bör vara 2^N - 1 
    std::vector<int> bst(primes.size());
    
    // Anropa den rekursiva build_bst-funktionen
    // Börja vid index 0, och använd helt intervall av primes
    build_bst(primes, bst, 0, 0, primes.size() - 1);
    
    return bst;
}

// Sök efter search_value i sökträdet
bool bst_search(const std::vector<int>& bst, int search_value) {
    // Starta från roten av trädet
    int current_index = 0;
    
    // Traversera trädet från roten
    while (current_index < bst.size() && bst[current_index] != 0) {
        if (bst[current_index] == search_value) {
            return true;
        }
        if (search_value < bst[current_index]) {
            // Gå vänster
            current_index = 2 * current_index + 1;
        }
        else {
            // Gå höger
            current_index = 2 * current_index + 2;
        }
    }
    
    return false;
}

std::vector<hash_node*> build_hashtable(
    const std::vector<int>& primes,
    int table_size
) {
    // Initiera hashtabellen med nullptr för alla platser
    std::vector<hash_node*> hashtable(table_size, nullptr);
    
    // För varje primtal i listan
    for (int prime : primes) {
        // Beräkna index med modulo
        int index = prime % table_size;
        
        // Skapa ny nod
        hash_node* new_node = new hash_node();
        new_node->data = prime;
        
        // Prepend: sätt in noden framst i listan
        new_node->next = hashtable[index];  // ny nod pekar på nuvarande huvud
        hashtable[index] = new_node;         // ny nod blir nya huvudet
    }
    
    return hashtable;
}

bool hashtable_search(const std::vector<hash_node*>& hashtable, int search_value, int table_size) {
    // Beräkna index med modulo
    int index = search_value % table_size;
    
    // Traversera listan på detta index
    hash_node* current = hashtable[index];
    while (current != nullptr) {
        if (current->data == search_value) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

void free_hashtable(std::vector<hash_node*>& hashtable) {
    for (hash_node* current : hashtable) {
        // Traversera hela kedjan och frigör varje nod för att undvika minnesläcka
        while (current != nullptr) {
            hash_node* next = current->next;  // spara nästa innan vi tar bort nuvarande
            delete current;
            current = next;
        }
    }
}
