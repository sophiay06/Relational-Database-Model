#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RPT.h"
#include "RD.h"
#include "RS.h"
#include "Part3Functions.h"

RPTHashTable select_RPT_Race(RPTHashTable table, const char* race) {
    RPTHashTable tobereturned = new_RPTHashTable(table->size);

    for(int i=0; i < table->size; i++) {
        RPT current = table->buckets[i];
        while(current != NULL) {
            if (race != NULL && strcmp(race, "*") != 0 && strcmp(current->race, race) != 0) {
                current = current->next;
                continue;
            }
            if (strcmp(race, current->race) == 0) {
                insert_RPT(tobereturned, current);
            }
            current = current->next;
        }
    }
    return tobereturned;
}


// PROJP FUNCTIONS: FOR 2)PROJECTION

int hash_int(int pid, int size) {
    return abs(pid) % size;
}


projP create_projP(int pid) {
    projP newEntry = (projP)malloc(sizeof(struct projP));
    if (newEntry != NULL) {
        // strncpy(newEntry->race, race, sizeof(newEntry->race) - 1);
        // newEntry->race[sizeof(newEntry->race) - 1] = '\0';
        newEntry->pid = pid;
        // strncpy(newEntry->time, time, sizeof(newEntry->time) - 1);
        // newEntry->time[sizeof(newEntry->time) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}


projPHashTable new_projPHashTable(int size) {
    projPHashTable table = (projPHashTable)malloc(sizeof(struct projPHashTable));
    table->size = size;
    table->buckets = (projP*)calloc(size, sizeof(projP));
    table->count = 0;
    return table;
}


void free_projPHashTable(projPHashTable table) {
    for (int i = 0; i < table->size; i++) {
        projP current = table->buckets[i];
        while (current != NULL) {
            projP next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}


int get_projP_pid(projP entry) {
    return entry->pid;
}


void insert_projP(projPHashTable table, projP entry) {
    int index = hash_int(entry->pid, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}


void print_projPTable(projPHashTable table) {
    int totalPIDs = 0;
    printf("PIDs in the hash table:\n");

    // Array to store PIDs for summary
    int pidList[table->size * 10];  // Assuming no more than 10 entries per bucket for simplicity
    int pidIndex = 0;

    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        projP current = table->buckets[i];
        while (current != NULL) {
            printf("[PID: %d] -> ", current->pid);
            pidList[pidIndex++] = current->pid; // Collect PIDs for the summary
            totalPIDs++; // Count the number of PIDs
            current = current->next;
        }
        printf("NULL\n");
    }

    // Print summary
    if (totalPIDs > 0) {
        printf("\nTotal PIDs Found: %d\n", totalPIDs);
        printf("List of PIDs: ");
        for (int i = 0; i < pidIndex; i++) {
            printf("%d", pidList[i]);
            if (i < pidIndex - 1) {
                printf(", ");
            }
        }
    } else {
        printf("\nNo PIDs found in the hash table.\n");
    }
}



projPHashTable proj_RPT_PId(RPTHashTable table, const char* race) {
    RPTHashTable selecttable = new_RPTHashTable(10);
    selecttable = select_RPT_Race(table, race);
    projPHashTable projtobereturned = new_projPHashTable(selecttable->size);
    for (int i = 0; i < selecttable->size; i++) {
        RPT current = selecttable->buckets[i];
        while(current != NULL) {
            if (current->pid != -1) {
                insert_projP(projtobereturned, create_projP(current->pid));
                current = current->next;
            }

        }
    }
    return projtobereturned;

}

//RDS FUNCTIONS FOR 3)JOIN

int hash_race_date_sponsor(const char* race, const char* date, const char* sponsor, int table_size) {
    char combined[150];  // Buffer to store concatenated Race and Date and Sponsor
    snprintf(combined, sizeof(combined), "%s%s%s", race, date, sponsor);  // Concatenate Race and Date and Sponsor

    int hash = 0;

    for (int i = 0; combined[i] != '\0'; i++) {
        hash = (hash * 17 + combined[i]) % table_size;  // Multiply by a prime and add ASCII value
    }

    return hash;
}

RDS create_RDS(const char* race, const char* date, const char* sponsor) {
    RDS newEntry = (RDS)malloc(sizeof(struct RDS));
    if (newEntry != NULL) {
        strncpy(newEntry->race, race, sizeof(newEntry->race) - 1);
        newEntry->race[sizeof(newEntry->race) - 1] = '\0';
        strncpy(newEntry->date, date, sizeof(newEntry->date) - 1);
        newEntry->date[sizeof(newEntry->date) - 1] = '\0';
        strncpy(newEntry->sponsor, sponsor, sizeof(newEntry->sponsor) - 1);
        newEntry->sponsor[sizeof(newEntry->sponsor) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}

RDSHashTable new_RDSHashTable(int size) {
    RDSHashTable table = (RDSHashTable)malloc(sizeof(struct RDSHashTable));
    table->size = size;
    table->buckets = (RDS*)calloc(size, sizeof(RDS));
    table->count = 0;
    return table;
}

void free_RDSHashTable(RDSHashTable table) {
    for (int i = 0; i < table->size; i++) {
        RDS current = table->buckets[i];
        while (current != NULL) {
            RDS next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}

const char* get_RDS_race(RDS entry) {
    return entry->race;
}
const char* get_RDS_date(RDS entry) {
    return entry->date;
}
const char* get_RDS_sponsor(RDS entry) {
    return entry->sponsor;
}

void insert_RDS(RDSHashTable table, RDS entry) {
    int index = hash_race_date_sponsor(entry->race, entry->date,entry->sponsor, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}

void print_RDSTable(RDSHashTable table) {
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        RDS current = table->buckets[i];
        while (current != NULL) {
            printf("[Race: %s, Date: %s, Sponsor: %s] -> ",
                   current->race, current->date, current->sponsor);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Function to join RD and RS on the Race attribute
RDSHashTable join_RD_RS(RDHashTable rdTable, RSHashTable rsTable) {
    RDSHashTable tobereturned = new_RDSHashTable(rdTable->size * rsTable->size);
    int match_found = 0; // Flag to track if any matches are found

    // Loop through all buckets in the RD hash table
    for (int i = 0; i < rdTable->size; i++) {
        RD currentRD = rdTable->buckets[i];
        while (currentRD != NULL) {
            // For each entry in RD, search RS for matching Race
            for (int j = 0; j < rsTable->size; j++) {
                RS currentRS = rsTable->buckets[j];
                while (currentRS != NULL) {
                    // Check if RD.Race matches RS.Race
                    if (strcmp(currentRD->race, currentRS->race) == 0) {
                        RDS currentRDS = create_RDS(currentRD->race, currentRD->date, currentRS->sponsor);
                        insert_RDS(tobereturned, currentRDS);
                        match_found = 1;
                    }
                    currentRS = currentRS->next; // Move to the next entry in RS
                }
            }
            currentRD = currentRD->next; // Move to the next entry in RD
        }
    }

    // Print a message if no matches were found
    if (!match_found) {
        printf("No matching entries found for the join.\n");
    }

    return tobereturned; // Return the resulting hash table
}


// Function to print the RDS hash table in the desired format
void print_RDSHashTable(RDSHashTable table) {
    int match_found = 0; // Flag to check if there are any entries
    for (int i = 0; i < table->size; i++) {
        RDS current = table->buckets[i];
        while (current != NULL) {
            // Print the entry in the desired format
            printf("Race: %s, Date: %s, Sponsor:%s\n",
                   current->race, current->date, current->sponsor);
            match_found = 1;
            current = current->next; // Move to the next entry in the bucket
        }
    }

    // Print a message if no entries are found
    if (!match_found) {
        printf("No matching entries found in the hash table.\n");
    }
}


//FUNCTIONS FOR 4)

RDSHashTable select_join_RD_RS_Date(RDHashTable RDtable, RSHashTable RStable, const char* date) {

    RDSHashTable jointable = new_RDSHashTable(RDtable->size);
    jointable = join_RD_RS(RDtable, RStable);

    RDSHashTable tobereturned = new_RDSHashTable(RDtable->size);

     for(int i=0; i < jointable->size; i++) {
         RDS current = jointable->buckets[i];

         while(current != NULL) {
             if (date != NULL && strcmp(date, "*") != 0 && strcmp(current->date, date) != 0) {
                 current = current->next;
                 continue;
             }
             if (strcmp(date, current->date) == 0) {
                 insert_RDS(tobereturned, current);
             }
             current = current->next;

         }
     }
     return tobereturned;
}

//PROJECTION FOR SPONSOR FUNCTIONS

int hash_sponsor(const char* sponsor, int size) {
    char combined[50];
    snprintf(combined, sizeof(combined), "%s", sponsor);

    int hash = 0;
    for (int i = 0; combined[i] != '\0'; i++) {
        hash = (hash * 31 + combined[i]) % size;  // Multiply by a prime and add ASCII value
    }

    return hash;
}


projSp create_projSp(const char* sponsor) {
    projSp newEntry = (projSp)malloc(sizeof(struct projSp));
    if (newEntry != NULL) {
        strncpy(newEntry->sponsor, sponsor, sizeof(newEntry->sponsor) - 1);
        newEntry->sponsor[sizeof(newEntry->sponsor) - 1] = '\0';
        newEntry->next = NULL;
    }
    return newEntry;
}


projSpHashTable new_projSpHashTable(int size) {
    projSpHashTable table = (projSpHashTable)malloc(sizeof(struct projSpHashTable));
    table->size = size;
    table->buckets = (projSp*)calloc(size, sizeof(projSp));
    table->count = 0;
    return table;
}


void free_projSpHashTable(projSpHashTable table) {
    for (int i = 0; i < table->size; i++) {
        projSp current = table->buckets[i];
        while (current != NULL) {
            projSp next = current->next;
            free(current);
            current = next;
        }
    }
    free(table->buckets);
    free(table);
}

void insert_projSp(projSpHashTable table, projSp entry) {
    int index = hash_sponsor(entry->sponsor, table->size);
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->count++;
}

void print_projSpTable(projSpHashTable table) {
    int totalSponsors = 0;

    printf("Sponsors in the hash table:\n");
    for (int i = 0; i < table->size; i++) {
        printf("Bucket %d: ", i);
        projSp current = table->buckets[i];
        while (current != NULL) {
            printf("[Sponsor: %s] -> ", current->sponsor);
            totalSponsors++; // Count the number of sponsors
            current = current->next;
        }
        printf("NULL\n");
    }

    // Print summary
    if (totalSponsors > 0) {
        printf("\nTotal Sponsors Found: %d\n", totalSponsors);
        printf("The hash table contains all the sponsors successfully.\n");
    } else {
        printf("\nNo sponsors found in the hash table.\n");
    }
}


projSpHashTable proj_RDS_Sp(RDSHashTable table) {
    projSpHashTable projtobereturned = new_projSpHashTable(table->size);
    for (int i = 0; i < table->size; i++) {
        RDS current = table->buckets[i];
        while (current != NULL) {
            // Check sponsor content without comparing to NULL
            if (strcmp(current->sponsor, "*") != 0) {
                insert_projSp(projtobereturned, create_projSp(current->sponsor));
            }
            current = current->next; // Move to the next entry
        }
    }
    return projtobereturned;
}

