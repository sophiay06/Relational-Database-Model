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
    // Create the hash tables
    PNCZHashTable PNCZ_Table = new_PNCZHashTable(11);
    RPTHashTable RPT_Table = new_RPTHashTable(11);
    if (PNCZ_Table == NULL || RPT_Table == NULL) {
        fprintf(stderr, "Failed to create hash tables.\n");
        return;
    }

    // Initialize the hash tables with data
    initialize_PNCZ_data(PNCZ_Table);
    initialize_RPT_data(RPT_Table);

    int match_found = 0;

    // (1) for each tuple t in StudentId-Name-Address-Phone do
    for (int i = 0; i < PNCZ_Table->size; i++) {
        PNCZ currentPNCZ = PNCZ_Table->buckets[i];
        while (currentPNCZ != NULL) {
            // (2) if t has “C. Brown” in its Name component then
            if (strcmp(currentPNCZ->name, name) == 0) {
                // (3) let i be the StudentId component of tuple t
                int pid = currentPNCZ->pid;

                // (4) for each tuple s in Course-StudentId-Grade do
                for (int j = 0; j < RPT_Table->size; j++) {
                    RPT currentRPT = RPT_Table->buckets[j];
                    while (currentRPT != NULL) {
                        // (5) if s has Course component “CS101” and StudentId component i
                        if (currentRPT->pid == pid && strcmp(currentRPT->race, race) == 0) {
                            // (6) print the Grade component of tuple s
                            printf("Participant %s with PID %d got a time of %s in race %s.\n",
                                   name, pid, currentRPT->time, race);
                            match_found = 1;
                        }
                        currentRPT = currentRPT->next;
                    }
                }
            }
            currentPNCZ = currentPNCZ->next;
        }
    }

    // If no match is found
    if (!match_found) {
        printf("No time found for %s in race %s.\n", name, race);
    }

    //Free the hash tables
    free_PNCZHashTable(PNCZ_Table);
    free_RPTHashTable(RPT_Table);
}


// Function to answer "On what date(s) did Name run a race sponsored by Sponsor?"
void query_dates_by_name_and_sponsor(const char* name, const char* sponsor) {
    // Create the hash tables
    PNCZHashTable PNCZ_Table = new_PNCZHashTable(11);
    RPTHashTable RPT_Table = new_RPTHashTable(11);
    RSHashTable RS_Table = new_RSHashTable(11);
    RDHashTable RD_Table = new_RDHashTable(11);
    if (PNCZ_Table == NULL || RPT_Table == NULL || RS_Table == NULL || RD_Table == NULL) {
        fprintf(stderr, "Failed to create hash tables.\n");
        return;
    }

    // Initialize the hash tables with data
    initialize_PNCZ_data(PNCZ_Table);
    initialize_RPT_data(RPT_Table);
    initialize_RS_data(RS_Table);
    initialize_RD_data(RD_Table);

    int match_found = 0;  // Flag to track if any matching entries are found

    // (1) for each tuple t in StudentId-Name-Address-Phone do
    for (int i = 0; i < PNCZ_Table->size; i++) {
        PNCZ currentPNCZ = PNCZ_Table->buckets[i];
        while (currentPNCZ != NULL) {
            // (2) if t has “C. Brown” in its Name component then
            if (strcmp(currentPNCZ->name, name) == 0) {
                // (3) let i be the StudentId component of tuple t
                int pid = currentPNCZ->pid;

                // (4) for each tuple s in Course-StudentId-Grade do
                for (int j = 0; j < RPT_Table->size; j++) {
                    RPT currentRPT = RPT_Table->buckets[j];
                    while (currentRPT != NULL) {
                        // Check if pid matches
                        if (currentRPT->pid == pid) {
                            const char* race = currentRPT->race;

                            // (5) for each tuple r in RS do
                            for (int k = 0; k < RS_Table->size; k++) {
                                RS currentRS = RS_Table->buckets[k];
                                while (currentRS != NULL) {
                                    // Check if race and sponsor match
                                    if (strcmp(currentRS->race, race) == 0 && strcmp(currentRS->sponsor, sponsor) == 0) {
                                        // (6) for each tuple d in RD do
                                        for (int l = 0; l < RD_Table->size; l++) {
                                            RD currentRD = RD_Table->buckets[l];
                                            while (currentRD != NULL) {
                                                // Check if race matches
                                                if (strcmp(currentRD->race, race) == 0) {
                                                    printf("Participant %s with PID %d ran in race %s sponsored by %s on date %s.\n",
                                                           name, pid, race, sponsor, currentRD->date);
                                                    match_found = 1;
                                                }
                                                currentRD = currentRD->next;
                                            }
                                        }
                                    }
                                    currentRS = currentRS->next;
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

    // If no matches were found
    if (!match_found) {
        printf("No matching entries found for %s with sponsor %s.\n", name, sponsor);
    }

    //Free the hash tables
    free_PNCZHashTable(PNCZ_Table);
    free_RPTHashTable(RPT_Table);
    free_RDHashTable(RD_Table);
    free_RSHashTable(RS_Table);
}

