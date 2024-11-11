#include <stdio.h>
#include <string.h>
#include "PNCZ.h"
#include "RPT.h"
#include "RD.h"
#include "RS.h"
#include "RQ.h"
#include "InitializeData.h"

// Function to answer "What time did Name get in Race?" and print all matches
void query_time_in_race(const char* name, const char* race) {
    PNCZHashTable PNCZ_Table = new_PNCZHashTable(10);
    RPTHashTable RPT_Table = new_RPTHashTable(10);
    if (PNCZ_Table == NULL|| RPT_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
    }
    initialize_PNCZ_data(PNCZ_Table);
    initialize_RPT_data(RPT_Table);

    int match_found = 0;

    // Step 1: Find all participant IDs (pids) for the given Name in PNCZ
    for (int i = 0; i < PNCZ_Table->size; i++) {
        PNCZ current = PNCZ_Table->buckets[i];
        while (current != NULL) {
            if (strcmp(current->name, name) == 0) {
                int pid = current->pid;  // Capture each pid associated with the given name

                // Step 2: Use the current pid and race to find the time in RPT
                for (int j = 0; j < RPT_Table->size; j++) {
                    RPT currentRPT = RPT_Table->buckets[j];
                    while (currentRPT != NULL) {
                        // Check if both pid and race match
                        if (currentRPT->pid == pid && strcmp(currentRPT->race, race) == 0) {
                            printf("Participant %s with PID %d got a time of %s in race %s.\n",
                                   name, pid, currentRPT->time, race);
                            match_found = 1;
                        }
                        currentRPT = currentRPT->next;
                    }
                }
            }
            current = current->next;
        }
    }

    // If no matching race and time were found, print a message
    if (!match_found) {
        printf("No time found for %s in race %s.\n", name, race);
    }
}


// Function to answer "On what date(s) did Name run a race sponsored by Sponsor?"
void query_dates_by_name_and_sponsor( const char* name, const char* sponsor) {
    PNCZHashTable PNCZ_Table = new_PNCZHashTable(10);
    RPTHashTable RPT_Table = new_RPTHashTable(10);
    RSHashTable RS_Table = new_RSHashTable(10);
    RDHashTable RD_Table = new_RDHashTable(10);
    if (PNCZ_Table == NULL|| RPT_Table == NULL || RS_Table == NULL || RD_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
    }
    initialize_PNCZ_data(PNCZ_Table);
    initialize_RPT_data(RPT_Table);
    initialize_RS_data(RS_Table);
    initialize_RD_data(RD_Table);

    int match_found = 0;  // Flag to track if any matching entries are found

    // Step 1: Find all participant IDs (pids) for the given Name in PNCZ
    for (int i = 0; i < PNCZ_Table->size; i++) {
        PNCZ currentPNCZ = PNCZ_Table->buckets[i];
        while (currentPNCZ != NULL) {
            if (strcmp(currentPNCZ->name, name) == 0) {
                int pid = currentPNCZ->pid;

                // Step 2: Find all races in RPT for the given pid
                for (int j = 0; j < RPT_Table->size; j++) {
                    RPT currentRPT = RPT_Table->buckets[j];
                    while (currentRPT != NULL) {
                        if (currentRPT->pid == pid) {
                            const char* race = currentRPT->race;

                            // Step 3: Check if the race is sponsored by the given Sponsor in RS
                            int sponsored = 0;
                            for (int k = 0; k < RS_Table->size; k++) {
                                RS currentRS = RS_Table->buckets[k];
                                while (currentRS != NULL) {
                                    if (strcmp(currentRS->race, race) == 0 && strcmp(currentRS->sponsor, sponsor) == 0) {
                                        sponsored = 1;
                                        break;
                                    }
                                    currentRS = currentRS->next;
                                }
                                if (sponsored) break;
                            }

                            // Step 4: If sponsored, find the date of the race in RD
                            if (sponsored) {
                                for (int l = 0; l < RD_Table->size; l++) {
                                    RD currentRD = RD_Table->buckets[l];
                                    while (currentRD != NULL) {
                                        if (strcmp(currentRD->race, race) == 0) {
                                            printf("Participant %s with PID %d ran in race %s sponsored by %s on date %s.\n",
                                                   name, pid, race, sponsor, currentRD->date);
                                            match_found = 1;
                                        }
                                        currentRD = currentRD->next;
                                    }
                                }
                            }
                        }
                        currentRPT = currentRPT->next;
                    }
                }
            }
            currentPNCZ = currentPNCZ->next;
        }
    }

    // If no matches were found, print a message
    if (!match_found) {
        printf("No matching entries found for %s with sponsor %s.\n", name, sponsor);
    }
}


