#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PNCZ.h"
#include "hash.h"

PNCZ create_PNCZ(int pid, const char* name, const char* city, int zip) {
    PNCZ newEntry = (PNCZ)malloc(sizeof(struct PNCZ));
    if (newEntry != NULL) {
        newEntry->pid = pid;
        strncpy(newEntry->name, name, sizeof(newEntry->name) - 1);
        newEntry->name[sizeof(newEntry->name) - 1] = '\0';
        strncpy(newEntry->city, city, sizeof(newEntry->city) - 1);
        newEntry->city[sizeof(newEntry->city) - 1] = '\0';
        newEntry->zip = zip;
        newEntry->next = NULL;
    }
    return newEntry;
}


PNCZHashTable new_PNCZHashTable(int size) {
    PNCZHashTable table = (PNCZHashTable)malloc(sizeof(struct PNCZHashTable));
    table->size = size;
    table->buckets = (PNCZ*)calloc(size, sizeof(PNCZ));
    table->count = 0;
    return table;
}


void free_PNCZHashTable(PNCZHashTable table) {
    for (int i = 0; i < table->size; i++) {
        PNCZ current = table->buckets[i];
        while (current != NULL) {
            PNCZ next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}


int get_PNCZ_pid(PNCZ entry) {
    return entry->pid;
}
const char* get_PNCZ_name(PNCZ entry) {
    return entry->name;
}
const char* get_PNCZ_city(PNCZ entry) {
    return entry->city;
}
int get_PNCZ_zip(PNCZ entry) {
    return entry->zip;
}


void insert_PNCZ(PNCZHashTable table, PNCZ entry) {
    int index = hash(entry->pid, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}


void lookup_PNCZ(PNCZHashTable table, int pid, const char* name, const char* city, int zip) {
    int found = 0;  // Flag to check if any entry is found

    // Loop through each bucket in the hash table
    for (int i = 0; i < table->size; i++) {
        PNCZ current = table->buckets[i];

        // Traverse each entry in the current bucket
        while (current != NULL) {
            // Match on pid if specified (not -1)
            if (pid != -1 && current->pid != pid) {
                current = current->next;
                continue;
            }
            // Match on name if specified (not "*")
            if (name != NULL && strcmp(name, "*") != 0 && strcmp(current->name, name) != 0) {
                current = current->next;
                continue;
            }
            // Match on city if specified (not "*")
            if (city != NULL && strcmp(city, "*") != 0 && strcmp(current->city, city) != 0) {
                current = current->next;
                continue;
            }
            // Match on zip if specified (not -1)
            if (zip != -1 && current->zip != zip) {
                current = current->next;
                continue;
            }

            // If all specified conditions match, print the entry
            printf("PID = %d, Name = %s, City = %s, Zip = %d\n",
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


void delete_PNCZ(PNCZHashTable table, int pid, const char* name, const char* city, int zip) {
    int start_bucket = 0;
    int end_bucket = table->size;
    int deleted = 0;  // Counter to track if any entries were deleted

    // If pid is not a wildcard, calculate the specific bucket
    if (pid != -1) {
        start_bucket = hash(pid, table->size);
        end_bucket = start_bucket + 1;
    }

    // Traverse the relevant buckets
    for (int i = start_bucket; i < end_bucket; i++) {
        PNCZ current = table->buckets[i];
        PNCZ prev = NULL;

        // Traverse the linked list at the current bucket
        while (current != NULL) {
            // Check if current node matches all specified criteria
            int match = 1;

            if (pid != -1 && current->pid != pid) match = 0;
            if (name != NULL && strcmp(name, "*") != 0 && strcmp(current->name, name) != 0) match = 0;
            if (city != NULL && strcmp(city, "*") != 0 && strcmp(current->city, city) != 0) match = 0;
            if (zip != -1 && current->zip != zip) match = 0;

            if (match) {
                // Entry matches; delete it
                if (prev == NULL) {
                    // First node in the bucket
                    table->buckets[i] = current->next;
                } else {
                    // Node somewhere in the middle or end
                    prev->next = current->next;
                }

                // Move to the next node and free the current node
                PNCZ to_delete = current;
                current = current->next;
                free(to_delete);
                table->count--;
                deleted = 1;  // Mark that we deleted at least one entry
            } else {
                // Move pointers if no deletion
                prev = current;
                current = current->next;
            }
        }
    }

    // Print the updated hash table if any entries were deleted
    if (deleted) {
        printf("Hash table after deletions:\n");
        print_PNCZTable(table);
    } else {
        printf("No matching entries found to delete.\n");
    }
}


void print_PNCZTable(PNCZHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        PNCZ current = table->buckets[i];
        while (current != NULL) {
            printf("[PID: %d, Name: %s, City: %s, Zip: %d] -> ",
                   current->pid, current->name, current->city, current->zip);
            current = current->next;
        }
        printf("NULL\n");
    }
}


