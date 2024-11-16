#ifndef PNCZ_H
#define PNCZ_H

struct PNCZ {
    int pid;
    char name[50];
    char city[50];
    int zip;
    struct PNCZ* next;
};
typedef struct PNCZ *PNCZ;

struct PNCZHashTable {
    int size;
    PNCZ* buckets;
    int count;
};
typedef struct PNCZHashTable *PNCZHashTable;

int hash_pncz(int pid, int size);

PNCZ create_PNCZ(int pid, const char* name, const char* city, int zip);
PNCZHashTable new_PNCZHashTable(int size);
void free_PNCZHashTable(PNCZHashTable table);

int get_PNCZ_pid(PNCZ entry);
const char* get_PNCZ_name(PNCZ entry);
const char* get_PNCZ_city(PNCZ entry);
int get_PNCZ_zip(PNCZ entry);

void insert_PNCZ(PNCZHashTable table, PNCZ entry);
void lookup_PNCZ(PNCZHashTable table, int pid, const char* name, const char* city, int zip);
void delete_PNCZ(PNCZHashTable table, int pid, const char* name, const char* city, int zip);

void print_PNCZTable(PNCZHashTable table);

#endif
