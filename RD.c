#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RD.h"

int hash_race_date(const char* race, const char* date, int table_size) {
    char combined[100];  // Buffer to store concatenated Race and Date
    snprintf(combined, sizeof(combined), "%s%s", race, date);  // Concatenate Race and Date

    int hash = 0;

    for (int i = 0; combined[i] != '\0'; i++) {
        hash = (hash * 17 + combined[i]) % table_size;  // Multiply by a prime and add ASCII value
    }

    return hash;
}

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


void free_RDHashTable(RDHashTable table) {
    for (int i = 0; i < table->size; i++) {
        RD current = table->buckets[i];
        while (current != NULL) {
            RD next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}


const char* get_RD_race(RD entry) {
    return entry->race;
}
const char* get_RD_date(RD entry) {
    return entry->date;
}


void insert_RD(RDHashTable table, RD entry) {
    int index = hash_race_date(entry->race, entry->date, table->size);
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
        start_bucket = hash_race_date(race, date, table->size);
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
        printf("Hash table after deletions:\n");
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
