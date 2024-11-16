#include <stdio.h>
#include <string.h>
#include "PNCZ.h"
#include "RPT.h"
#include "RD.h"
#include "RS.h"
#include "RQ.h"

// Function to select rows in RPT where Race matches the given value
void select_RPT_Race(RPTHashTable rptTable, const char* race) {
    //printf("Selecting rows in RPT where Race = '%s':\n", race);
    printf("Executing σRace= '%s'(RPT)\n", race);
    int match_found = 0;  // Flag to track if any matches are found

    // Loop through all buckets in the hash table
    for (int i = 0; i < rptTable->size; i++) {
        RPT current = rptTable->buckets[i];
        while (current != NULL) {
            // Check if the Race matches the provided value
            if (strcmp(current->race, race) == 0) {
                printf("Race: %s, PId: %d, Time: %s\n", current->race, current->pid, current->time);
                match_found = 1;
            }
            current = current->next;  // Move to the next entry in the bucket
        }
    }

    // If no matches were found, print a message
    if (!match_found) {
        printf("No entries found for Race = '%s'.\n", race);
    }
}


// Function to project the PId column from the RPT table for a specific race
void project_RPT_PId(RPTHashTable rptTable, const char* race) {
    printf("Projecting PId column from RPT where Race = '%s':\n", race);

    int match_found = 0;  // Flag to track if any matches are found

    // Loop through all buckets in the RPT hash table
    for (int i = 0; i < rptTable->size; i++) {
        RPT current = rptTable->buckets[i];
        while (current != NULL) {
            // Check if the Race matches the provided value
            if (strcmp(current->race, race) == 0) {
                printf("PId: %d\n", current->pid);  // Print the PId column
                match_found = 1;
            }
            current = current->next;  // Move to the next entry in the bucket
        }
    }

    // If no matches were found, print a message
    if (!match_found) {
        printf("No entries found for Race = '%s'.\n", race);
    }
}


// Function to join RD and RS on the Race attribute
void join_RD_RS(RDHashTable rdTable, RSHashTable rsTable) {
    printf("Joining RD and RS on Race:\n");

    int match_found = 0;  // Flag to track if any matches are found

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
                        printf("Race: %s, Date: %s, Sponsor: %s\n",
                               currentRD->race, currentRD->date, currentRS->sponsor);
                        match_found = 1;
                    }
                    currentRS = currentRS->next;  // Move to the next entry in RS
                }
            }
            currentRD = currentRD->next;  // Move to the next entry in RD
        }
    }

    // If no matches were found, print a message
    if (!match_found) {
        printf("No matching entries found for the join.\n");
    }
}


// Function to execute πSponsor(σDate=“2023-10-02”(RD ▷◁ RS))
void query_project_sponsor_by_date(RDHashTable rdTable, RSHashTable rsTable, const char* target_date) {
    printf("Executing πSponsor(σDate='%s'(RD ▷◁ RS)):\n", target_date);

    int match_found = 0;  // Flag to track if any matches are found

    // Step 1: Join RD and RS on Race
    for (int i = 0; i < rdTable->size; i++) {
        RD currentRD = rdTable->buckets[i];
        while (currentRD != NULL) {
            for (int j = 0; j < rsTable->size; j++) {
                RS currentRS = rsTable->buckets[j];
                while (currentRS != NULL) {
                    // Check if RD.Race matches RS.Race
                    if (strcmp(currentRD->race, currentRS->race) == 0) {
                        // Step 2: Selection (σDate=“2023-10-02”)
                        if (strcmp(currentRD->date, target_date) == 0) {
                            // Step 3: Projection (πSponsor)
                            printf("Sponsor: %s\n", currentRS->sponsor);
                            match_found = 1;
                        }
                    }
                    currentRS = currentRS->next;  // Move to the next entry in RS
                }
            }
            currentRD = currentRD->next;  // Move to the next entry in RD
        }
    }

    // If no matches were found, print a message
    if (!match_found) {
        printf("No sponsors found for races on date '%s'.\n", target_date);
    }
}
