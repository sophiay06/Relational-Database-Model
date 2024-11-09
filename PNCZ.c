#include "PNCZ.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define the PNCZ struct
struct PNCZ {
    char pid[10];
    char name[50];
    char city[50];
    char zip[10];
    struct PNCZ* next;  // For chaining in hash buckets
};

// Define the PNCZHashTable struct privately in PNCZ.c
struct PNCZHashTable {
    int size;
    PNCZ* buckets;  // Array of pointers to PNCZ nodes (linked list for each bucket)
    int count;
};

// Hash function to compute the bucket index
static int hash(const char* pid, int size) {
    int pid_num = atoi(pid);  // Convert pid to an integer
    return pid_num % size;
}

// Create a new PNCZ entry
PNCZ create_PNCZ(const char* pid, const char* name, const char* city, const char* zip) {
    PNCZ newEntry = (PNCZ)malloc(sizeof(struct PNCZ));
    if (newEntry != NULL) {
        strncpy(newEntry->pid, pid, sizeof(newEntry->pid) - 1);
        newEntry->pid[sizeof(newEntry->pid) - 1] = '\0';  // Ensure null-termination
        strncpy(newEntry->name, name, sizeof(newEntry->name) - 1);
        newEntry->name[sizeof(newEntry->name) - 1] = '\0';
        strncpy(newEntry->city, city, sizeof(newEntry->city) - 1);
        newEntry->city[sizeof(newEntry->city) - 1] = '\0';
        strncpy(newEntry->zip, zip, sizeof(newEntry->zip) - 1);
        newEntry->zip[sizeof(newEntry->zip) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}



// Create a new PNCZHashTable
PNCZHashTable new_PNCZHashTable(int size) {
    PNCZHashTable table = (PNCZHashTable)malloc(sizeof(struct PNCZHashTable));
    table->size = size;
    table->buckets = (PNCZ*)calloc(size, sizeof(PNCZ));
    table->count = 0;
    return table;
}

// Accessor functions
const char* get_PNCZ_pid(PNCZ entry) {
    return entry->pid;
}
const char* get_PNCZ_name(PNCZ entry) {
    return entry->name;
}
const char* get_PNCZ_city(PNCZ entry) {
    return entry->city;
}
const char* get_PNCZ_zip(PNCZ entry) {
    return entry->zip;
}
PNCZ get_PNCZ_next(PNCZ entry) {
    return entry->next;
}

// Free the PNCZHashTable and all its entries
void free_PNCZHashTable(PNCZHashTable table) {
    for (int i = 0; i < table->size; i++) {
        PNCZ current = table->buckets[i];
        while (current != NULL) {
            PNCZ next = current->next;
            free(current);  // Free each PNCZ node
            current = next;
        }
    }
    free(table->buckets);  // Free the array of bucket pointers
    free(table);            // Free the table structure itself
}


// Insert a new PNCZ entry into the hashtable
void insert_PNCZ(PNCZHashTable table, PNCZ entry) {
    int index = hash(entry->pid, table->size);  // Use updated hash function
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}

// Look up a PNCZ entry by pid
void lookup_PNCZ(PNCZHashTable table, const char* pid, const char* name, const char* city, const char* zip) {
    int found = 0;  // Flag to check if any entry is found

    // Loop through each bucket in the hash table
    for (int i = 0; i < table->size; i++) {
        PNCZ current = table->buckets[i];

        // Traverse each entry in the current bucket
        while (current != NULL) {
            // Match on pid if specified (not "*")
            if (strcmp(pid, "*") != 0 && strcmp(current->pid, pid) != 0) {
                current = current->next;
                continue;
            }
            // Match on name if specified (not "*")
            if (strcmp(name, "*") != 0 && strcmp(current->name, name) != 0) {
                current = current->next;
                continue;
            }
            // Match on city if specified (not "*")
            if (strcmp(city, "*") != 0 && strcmp(current->city, city) != 0) {
                current = current->next;
                continue;
            }
            // Match on zip if specified (not "*")
            if (strcmp(zip, "*") != 0 && strcmp(current->zip, zip) != 0) {
                current = current->next;
                continue;
            }

            // If all specified conditions match, print the entry
            printf("PID = %s, Name = %s, City = %s, Zip = %s\n",
                   current->pid, current->name, current->city, current->zip);
            found = 1;

            // Move to the next entry in the bucket
            current = current->next;
        }
    }

    if (!found) {
        printf("No matching entries found.\n");
    }
}


// Remove a PNCZ entry by pid
void remove_PNCZ(PNCZHashTable table, const char* pid) {
    int index = hash(pid, table->size);
    PNCZ current = table->buckets[index];
    PNCZ prev = NULL;
    while (current != NULL) {
        if (strcmp(current->pid, pid) == 0) {
            if (prev == NULL) {
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            table->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Print all entries in the PNCZHashTable
void print_PNCZTable(PNCZHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        PNCZ current = table->buckets[i];
        while (current != NULL) {
            printf("[PID: %s, Name: %s, City: %s, Zip: %s] -> ",
                   current->pid, current->name, current->city, current->zip);
            current = current->next;
        }
        printf("NULL\n");
    }
}


