#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS.h"

static int hash_race(const char* race, int table_size) {
    unsigned int hash_value = 0;
    for (int i = 0; race[i] != '\0'; i++) {
        hash_value += (unsigned int)race[i];
    }
    return hash_value % table_size;
}


RS create_RS(const char* race, const char* sponsor) {
    RS newEntry = (RS)malloc(sizeof(struct RS));
    if (newEntry != NULL) {
        strncpy(newEntry->race, race, sizeof(newEntry->race) - 1);
        newEntry->race[sizeof(newEntry->race) - 1] = '\0';
        strncpy(newEntry->sponsor, sponsor, sizeof(newEntry->sponsor) - 1);
        newEntry->sponsor[sizeof(newEntry->sponsor) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}


RSHashTable new_RSHashTable(int size) {
    RSHashTable table = (RSHashTable)malloc(sizeof(struct RSHashTable));
    table->size = size;
    table->buckets = (RS*)calloc(size, sizeof(RS));
    table->count = 0;
    return table;
}


void free_RSHashTable(RSHashTable table) {
    for (int i = 0; i < table->size; i++) {
        RS current = table->buckets[i];
        while (current != NULL) {
            RS next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}


const char* get_RS_race(RS entry) {
    return entry->race;
}
const char* get_RS_sponsor(RS entry) {
    return entry->sponsor;
}


void insert_RS(RSHashTable table, RS entry) {
    int index = hash_race(entry->race, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}


void lookup_RS(RSHashTable table, const char* race, const char* sponsor) {
    int found = 0;  // Flag to check if any entry is found

    // Loop through each bucket in the hash table
    for (int i = 0; i < table->size; i++) {
        RS current = table->buckets[i];

        // Traverse each entry in the current bucket
        while (current != NULL) {
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) {
                current = current->next;
                continue;
            }
            if (sponsor != NULL && strcmp(sponsor, "*") != 0 && strcmp(current->sponsor, sponsor) != 0) {
                current = current->next;
                continue;
            }

            // If all specified conditions match, print the entry
            printf("Race = %s, Sponsor = %s\n",
                   current->race, current->sponsor);
            found = 1;

            // Move to the next entry in the bucket
            current = current->next;
        }
    }

    if (!found) {
        printf("No matching entries found.\n");
    }
}


void delete_RS(RSHashTable table, const char* race, const char* sponsor) {
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
        RS current = table->buckets[i];
        RS prev = NULL;

        // Traverse the linked list at the current bucket
        while (current != NULL) {
            // Check if current node matches all specified criteria
            int match = 1;

            // Match on race if specified and not a wildcard
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            // Match on sponsor if specified and not a wildcard
            if (sponsor != NULL && strcmp(sponsor, "*") != 0 && strcmp(current->sponsor, sponsor) != 0) match = 0;

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
                RS to_delete = current;
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
        print_RSTable(table);
    } else {
        printf("No matching entries found to delete.\n");
    }
}


void print_RSTable(RSHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        RS current = table->buckets[i];
        while (current != NULL) {
            printf("[Race: %s, Sponsor: %s] -> ",
                   current->race, current->sponsor);
            current = current->next;
        }
        printf("NULL\n");
    }
}
