#ifndef RS_H
#define RS_H

struct RS {
    char race[50];
    char sponsor[20];
    struct RS* next;
};
typedef struct RS *RS;

struct RSHashTable {
    int size;
    RS* buckets;
    int count;
};
typedef struct RSHashTable *RSHashTable;

int hash_race_sponsor(const char* race, const char* sponsor, int table_size);

RS create_RS(const char* race, const char* sponsor);
RSHashTable new_RSHashTable(int size);
void free_RSHashTable(RSHashTable table);

const char* get_RS_race(RS entry);
const char* get_RS_sponsor(RS entry);

void insert_RS(RSHashTable table, RS entry);
void lookup_RS(RSHashTable table, const char* race, const char* sponsor);
void delete_RS(RSHashTable table, const char* race, const char* sponsor);

void print_RSTable(RSHashTable table);

#endif