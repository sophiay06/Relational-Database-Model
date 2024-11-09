#ifndef RPT_H
#define RPT_H

typedef struct RPT *RPT;
typedef struct RPTHashTable *RPTHashTable;

RPT create_RPT(const char* race, int pid, const char* time);
RPTHashTable new_RPTHashTable(int size);
static int hash(int pid, int size);

const char* get_RPT_race(RPT entry);
int get_RPT_pid(RPT entry);
const char* get_RPT_time(RPT entry);

void free_RPTHashTable(RPTHashTable table);
void insert_RPT(RPTHashTable table, RPT entry);

void lookup_RPT(RPTHashTable table, const char* race, int pid, const char* time);
void delete_RPT(RPTHashTable table, const char* race, int pid, const char* time);

void print_RPTTable(RPTHashTable table);


#endif