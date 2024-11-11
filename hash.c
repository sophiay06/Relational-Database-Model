#include <stdlib.h>


int hash(int pid, int size) {
    return abs(pid) % size;
}

int hash_race(const char* race, int table_size) {
    unsigned int hash_value = 0;
    for (int i = 0; race[i] != '\0'; i++) {
        hash_value += (unsigned int)race[i];
    }
    return hash_value % table_size;
}