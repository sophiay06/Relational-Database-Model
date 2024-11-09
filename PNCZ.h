#ifndef PNCZ_H
#define PNCZ_H

typedef struct PNCZ *PNCZ;
typedef struct PNCZHashTable *PNCZHashTable;
PNCZ create_PNCZ(const char* pid, const char* name, const char* city, const char* zip);

// Function prototypes for managing the PNCZ hashtable
PNCZHashTable new_PNCZHashTable(int size);
void free_PNCZHashTable(PNCZHashTable table);
void insert_PNCZ(PNCZHashTable table, PNCZ entry);
void lookup_PNCZ(PNCZHashTable table, const char* pid, const char* name, const char* city, const char* zip);
void remove_PNCZ(PNCZHashTable table, const char* pid);
void print_PNCZTable(PNCZHashTable table);

// Accessor function prototypes
const char* get_PNCZ_pid(PNCZ entry);
const char* get_PNCZ_name(PNCZ entry);
const char* get_PNCZ_city(PNCZ entry);
const char* get_PNCZ_zip(PNCZ entry);
PNCZ get_PNCZ_next(PNCZ entry);
#endif
