#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RPT.h"

int hash_rpt(int pid, int size) {
    return abs(pid) % size;
}

RPT create_RPT(const char* race, int pid, const char* time) {
    RPT newEntry = (RPT)malloc(sizeof(struct RPT));
    if (newEntry != NULL) {
        strncpy(newEntry->race, race, sizeof(newEntry->race) - 1);
        newEntry->race[sizeof(newEntry->race) - 1] = '\0';
        newEntry->pid = pid;
        strncpy(newEntry->time, time, sizeof(newEntry->time) - 1);
        newEntry->time[sizeof(newEntry->time) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}


RPTHashTable new_RPTHashTable(int size) {
    RPTHashTable table = (RPTHashTable)malloc(sizeof(struct RPTHashTable));
    table->size = size;
    table->buckets = (RPT*)calloc(size, sizeof(RPT));
    table->count = 0;
    return table;
}


void free_RPTHashTable(RPTHashTable table) {
    for (int i = 0; i < table->size; i++) {
        RPT current = table->buckets[i];
        while (current != NULL) {
            RPT next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}


const char* get_RPT_race(RPT entry) {
    return entry->race;
}
int get_RPT_pid(RPT entry) {
    return entry->pid;
}
const char* get_RPT_time(RPT entry) {
    return entry->time;
}


void insert_RPT(RPTHashTable table, RPT entry) {
    int index = hash_rpt(entry->pid, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}


void lookup_RPT(RPTHashTable table, const char* race, int pid, const char* time) {
    int found = 0;  // Flag to check if any entry is found

    // Loop through each bucket in the hash table
    for (int i = 0; i < table->size; i++) {
        RPT current = table->buckets[i];

        // Traverse each entry in the current bucket
        while (current != NULL) {
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) {
                current = current->next;
                continue;
            }
            if (pid != -1 && current->pid != pid) {
                current = current->next;
                continue;
            }
            if (time != NULL && strcmp(time, "*") != 0 && strcmp(current->time, time) != 0) {
                current = current->next;
                continue;
            }

            // If all specified conditions match, print the entry
            printf("Race = %s, PID = %d, Time = %s\n",
                   current->race, current->pid, current->time);
            found = 1;

            // Move to the next entry in the bucket
            current = current->next;
        }
    }

    if (!found) {
        printf("No matching entries found.\n");
    }
}


void delete_RPT(RPTHashTable table, const char* race, int pid, const char* time) {
    int start_bucket = 0;
    int end_bucket = table->size;
    int deleted = 0;  // Counter to track if any entries were deleted

    // If pid is not a wildcard, calculate the specific bucket
    if (pid != -1) {
        start_bucket = hash_rpt(pid, table->size);
        end_bucket = start_bucket + 1;
    }

    // Traverse the relevant buckets
    for (int i = start_bucket; i < end_bucket; i++) {
        RPT current = table->buckets[i];
        RPT prev = NULL;

        // Traverse the linked list at the current bucket
        while (current != NULL) {
            // Check if current node matches all specified criteria
            int match = 1;

            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) match = 0;
            if (pid != -1 && current->pid != pid) match = 0;
            if (time != NULL && strcmp(time, "*") != 0 && strcmp(current->time, time) != 0) match = 0;

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
                RPT to_delete = current;
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
        print_RPTTable(table);
    } else {
        printf("No matching entries found to delete.\n");
    }
}


void print_RPTTable(RPTHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        RPT current = table->buckets[i];
        while (current != NULL) {
            printf("[Race: %s, PID: %d, Time: %s] -> ",
                   current->race, current->pid, current->time);
            current = current->next;
        }
        printf("NULL\n");
    }
}
