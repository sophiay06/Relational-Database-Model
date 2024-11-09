#ifndef RQ_H
#define RQ_H

typedef struct RQ *RQ;
typedef struct RQHashTable *RQHashTable;
static int hash_race(const char* race, int table_size);
RQ create_RQ(const char* race, const char* qualifier);
RQHashTable new_RQHashTable(int size);


const char* get_RQ_race(RQ entry);
const char* get_RQ_qualifier(RQ entry);

void free_RQHashTable(RQHashTable table);
void insert_RQ(RQHashTable table, RQ entry);

void lookup_RQ(RQHashTable table, const char* race, const char* qualifier);
void delete_RQ(RQHashTable table, const char* race, const char* qualifier);

void print_RQTable(RQHashTable table);


#endif