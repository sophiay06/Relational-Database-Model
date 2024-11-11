#ifndef RD_H
#define RD_H

struct RD {
    char race[50];
    char date[15];
    struct RD* next;
};
typedef struct RD *RD;

struct RDHashTable {
    int size;
    RD* buckets;
    int count;
};
typedef struct RDHashTable *RDHashTable;

static int hash_race(const char* race, int table_size);
RD create_RD(const char* race, const char* date);
RDHashTable new_RDHashTable(int size);
void free_RDHashTable(RDHashTable table);

const char* get_RD_race(RD entry);
const char* get_RD_date(RD entry);

void insert_RD(RDHashTable table, RD entry);
void lookup_RD(RDHashTable table, const char* race, const char* date);
void delete_RD(RDHashTable table, const char* race, const char* date);

void print_RDTable(RDHashTable table);

#endif