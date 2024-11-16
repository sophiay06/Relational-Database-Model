#ifndef RPT_H
#define RPT_H

struct RPT {
    char race[50];
    int pid;
    char time[10];
    struct RPT* next;
};
typedef struct RPT *RPT;

struct RPTHashTable {
    int size;
    RPT* buckets;
    int count;
};
typedef struct RPTHashTable *RPTHashTable;

int hash_rpt(int pid, int size);

RPT create_RPT(const char* race, int pid, const char* time);
RPTHashTable new_RPTHashTable(int size);
void free_RPTHashTable(RPTHashTable table);

const char* get_RPT_race(RPT entry);
int get_RPT_pid(RPT entry);
const char* get_RPT_time(RPT entry);

void insert_RPT(RPTHashTable table, RPT entry);
void lookup_RPT(RPTHashTable table, const char* race, int pid, const char* time);
void delete_RPT(RPTHashTable table, const char* race, int pid, const char* time);

void print_RPTTable(RPTHashTable table);

#endif