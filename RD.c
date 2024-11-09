#include "RD.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define the RD struct
struct RD {
    char race[50];
    char date[15];
    struct RD* next;  // For chaining in hash buckets
};

struct RDHashTable {
    int size;
    RD* buckets;  // Array of pointers to PNCZ nodes (linked list for each bucket)
    int count;
};

static int hash_race(const char* race, int table_size) {
    unsigned int hash_value = 0;
    for (int i = 0; race[i] != '\0'; i++) {
        hash_value += (unsigned int)race[i];
    }
    return hash_value % table_size;
}

// Create a new RD entry
RD create_RD(const char* race, const char* date) {
    RD newEntry = (RD)malloc(sizeof(struct RD));
    if (newEntry != NULL) {
        strncpy(newEntry->race, race, sizeof(newEntry->race) - 1);
        newEntry->race[sizeof(newEntry->race) - 1] = '\0';
        strncpy(newEntry->date, date, sizeof(newEntry->date) - 1);
        newEntry->date[sizeof(newEntry->date) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}

RDHashTable new_RDHashTable(int size) {
    RDHashTable table = (RDHashTable)malloc(sizeof(struct RDHashTable));
    table->size = size;
    table->buckets = (RD*)calloc(size, sizeof(RD));
    table->count = 0;
    return table;
}

const char* get_RD_race(RD entry) {
    return entry->race;
}

const char* get_RD_date(RD entry) {
    return entry->date;
}

void free_RDHashTable(RDHashTable table) {
    for (int i = 0; i < table->size; i++) {
        RD current = table->buckets[i];
        while (current != NULL) {
            RD next = current->next;
            free(current);  // Free each PNCZ node
            current = next;
        }
    }
    free(table->buckets);  // Free the array of bucket pointers
    free(table);            // Free the table structure itself
}

void insert_RD(RDHashTable table, RD entry) {
    int index = hash_race(entry->race, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}

void lookup_RD(RDHashTable table, const char* race, const char* date) {
    int found = 0;  // Flag to check if any entry is found

    // Loop through each bucket in the hash table
    for (int i = 0; i < table->size; i++) {
        RD current = table->buckets[i];

        // Traverse each entry in the current bucket
        while (current != NULL) {
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) {
                current = current->next;
                continue;
            }
            if (date != NULL && strcmp(date, "*") != 0 && strcmp(current->date, date) != 0) {
                current = current->next;
                continue;
            }

            // If all specified conditions match, print the entry
            printf("Race = %s, Date = %s\n",
                   current->race, current->date);
            found = 1;

            // Move to the next entry in the bucket
            current = current->next;
        }
    }

    if (!found) {
        printf("No matching entries found.\n");
    }
}

void delete_RD(RDHashTable table, const char* race, const char* date) {
    int start_bucket = 0;
    int end_bucket = table->size;
    int deleted = 0;  // Counter to track if any entries were deleted

    // If pid is not a wildcard, calculate the specific bucket
    if (race != NULL) {
        start_bucket = hash_race(race, table->size);
        end_bucket = start_bucket + 1;
    }

    // Traverse the relevant buckets
    for (int i = start_bucket; i < end_bucket; i++) {
        RD current = table->buckets[i];
        RD prev = NULL;

        // Traverse the linked list at the current bucket
        while (current != NULL) {
            // Check if current node matches all specified criteria
            int match = 1;

            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (date != NULL && strcmp(date, "*") != 0 && strcmp(current->date, date) != 0) match = 0;

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
                RD to_delete = current;
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
        printf("\nHash table after deletions:\n");
        print_RDTable(table);
    } else {
        printf("No matching entries found to delete.\n");
    }
}

void print_RDTable(RDHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        RD current = table->buckets[i];
        while (current != NULL) {
            printf("[Race: %s, Date: %s] -> ",
                   current->race, current->date);
            current = current->next;
        }
        printf("NULL\n");
    }
}
