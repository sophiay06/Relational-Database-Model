#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RQ.h"

static int hash_race(const char* race, int table_size) {
    unsigned int hash_value = 0;
    for (int i = 0; race[i] != '\0'; i++) {
        hash_value += (unsigned int)race[i];
    }
    return hash_value % table_size;
}


RQ create_RQ(const char* race, const char* qualifier) {
    RQ newEntry = (RQ)malloc(sizeof(struct RQ));
    if (newEntry != NULL) {
        strncpy(newEntry->race, race, sizeof(newEntry->race) - 1);
        newEntry->race[sizeof(newEntry->race) - 1] = '\0';
        strncpy(newEntry->qualifier, qualifier, sizeof(newEntry->qualifier) - 1);
        newEntry->qualifier[sizeof(newEntry->qualifier) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}


RQHashTable new_RQHashTable(int size) {
    RQHashTable table = (RQHashTable)malloc(sizeof(struct RQHashTable));
    table->size = size;
    table->buckets = (RQ*)calloc(size, sizeof(RQ));
    table->count = 0;
    return table;
}


void free_RQHashTable(RQHashTable table) {
    for (int i = 0; i < table->size; i++) {
        RQ current = table->buckets[i];
        while (current != NULL) {
            RQ next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}


const char* get_RQ_race(RQ entry) {
    return entry->race;
}
const char* get_RQ_qualifier(RQ entry) {
    return entry->qualifier;
}


void insert_RQ(RQHashTable table, RQ entry) {
    int index = hash_race(entry->race, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}


void lookup_RQ(RQHashTable table, const char* race, const char* qualifier) {
    int found = 0;  // Flag to check if any entry is found

    // Loop through each bucket in the hash table
    for (int i = 0; i < table->size; i++) {
        RQ current = table->buckets[i];

        // Traverse each entry in the current bucket
        while (current != NULL) {
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) {
                current = current->next;
                continue;
            }
            if (qualifier != NULL && strcmp(qualifier, "*") != 0 && strcmp(current->qualifier, qualifier) != 0) {
                current = current->next;
                continue;
            }

            // If all specified conditions match, print the entry
            printf("Race = %s, Qualifier = %s\n",
                   current->race, current->qualifier);
            found = 1;

            // Move to the next entry in the bucket
            current = current->next;
        }
    }

    if (!found) {
        printf("No matching entries found.\n");
    }
}


void delete_RQ(RQHashTable table, const char* race, const char* qualifier) {
    int start_bucket = 0;
    int end_bucket = table->size;
    int deleted = 0;  // Counter to track if any entries were deleted

    // If race is specified and not a wildcard, calculate the specific bucket
    if (race != NULL && strcmp(race, "*") != 0) {
        start_bucket = hash_race(race, table->size);
        end_bucket = start_bucket + 1;
    }

    // Traverse the relevant buckets
    for (int i = start_bucket; i < end_bucket; i++) {
        RQ current = table->buckets[i];
        RQ prev = NULL;

        // Traverse the linked list at the current bucket
        while (current != NULL) {
            // Check if current node matches all specified criteria
            int match = 1;

            // Match on race if specified and not a wildcard
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            // Match on qualifier if specified and not a wildcard
            if (qualifier != NULL && strcmp(qualifier, "*") != 0 && strcmp(current->qualifier, qualifier) != 0) match = 0;

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
                RQ to_delete = current;
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
        print_RQTable(table);
    } else {
        printf("No matching entries found to delete.\n");
    }
}


void print_RQTable(RQHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        RQ current = table->buckets[i];
        while (current != NULL) {
            printf("[Race: %s, Sponsor: %s] -> ",
                   current->race, current->qualifier);
            current = current->next;
        }
        printf("NULL\n");
    }
}
