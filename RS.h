#ifndef RS_H
#define RS_H

typedef struct RS *RS;
typedef struct RSHashTable *RSHashTable;
static int hash_race(const char* race, int table_size);
RS create_RS(const char* race, const char* sponsor);
RSHashTable new_RSHashTable(int size);


const char* get_RS_race(RS entry);
const char* get_RS_sponsor(RS entry);

void free_RSHashTable(RSHashTable table);
void insert_RS(RSHashTable table, RS entry);

void lookup_RS(RSHashTable table, const char* race, const char* sponsor);
void delete_RS(RSHashTable table, const char* race, const char* sponsor);

void print_RSTable(RSHashTable table);


#endif