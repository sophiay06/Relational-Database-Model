#ifndef RD_H
#define RD_H

typedef struct RD *RD;
typedef struct RDHashTable *RDHashTable;
static int hash_race(const char* race, int table_size);
RD create_RD(const char* race, const char* date);
RDHashTable new_RDHashTable(int size);


const char* get_RD_race(RD entry);
const char* get_RD_date(RD entry);

void free_RDHashTable(RDHashTable table);
void insert_RD(RDHashTable table, RD entry);

void lookup_RD(RDHashTable table, const char* race, const char* date);
void delete_RD(RDHashTable table, const char* race, const char* date);

void print_RDTable(RDHashTable table);


#endif