#ifndef RQ_H
#define RQ_H

struct RQ {
    char race[50];
    char qualifier[20];
    struct RQ* next;
};
typedef struct RQ *RQ;

struct RQHashTable {
    int size;
    RQ* buckets;
    int count;
};
typedef struct RQHashTable *RQHashTable;

RQ create_RQ(const char* race, const char* qualifier);
RQHashTable new_RQHashTable(int size);
void free_RQHashTable(RQHashTable table);

const char* get_RQ_race(RQ entry);
const char* get_RQ_qualifier(RQ entry);

void insert_RQ(RQHashTable table, RQ entry);
void lookup_RQ(RQHashTable table, const char* race, const char* qualifier);
void delete_RQ(RQHashTable table, const char* race, const char* qualifier);

void print_RQTable(RQHashTable table);

#endif