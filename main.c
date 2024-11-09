#include <stdio.h>
#include "PNCZ.h"  // Include PNCZ functions

void initialize_PNCZ_data(PNCZHashTable table) {
    printf("Initializing PNCZ database with initial data:\n");

    insert_PNCZ(table, create_PNCZ("67815", "E. Allen", "Clarkson", "14642"));
    insert_PNCZ(table, create_PNCZ("37435", "J. Thomas", "Churchville", "14643"));
    insert_PNCZ(table, create_PNCZ("41222", "H. Evans", "North Gates", "14621"));
    insert_PNCZ(table, create_PNCZ("31444", "E. Allen", "Pittsford", "14559"));
    insert_PNCZ(table, create_PNCZ("89602", "J. Thomas", "Hamlin", "14651"));
    insert_PNCZ(table, create_PNCZ("69441", "O. Price", "Hamlin", "14506"));

    print_PNCZTable(table);
}

int main() {
    // Step 1: Create a new PNCZHashTable
    int tableSize = 10;
    PNCZHashTable pncTable = new_PNCZHashTable(tableSize);
    if (pncTable == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }

    //Initialize tables
    initialize_PNCZ_data(pncTable);

    // Perform additional operations (lookups, deletions, etc.)
    printf("\nDemonstrating operations:\n");

    // Example of a lookup operation
    /*
    int searchPID = 67815;
    PNCZ foundEntry = lookup_PNCZ(pncTable, searchPID);
    if (foundEntry != NULL) {
        printf("Found entry: PID = %d, Name = %s, City = %s, Zip = %d\n",
               get_PNCZ_pid(foundEntry), get_PNCZ_name(foundEntry),
               get_PNCZ_city(foundEntry), get_PNCZ_zip(foundEntry));
    } else {
        printf("Entry with PID %d not found.\n", searchPID);
    }
*/
    printf("Lookup for entries with Name 'J. Thomas' and any PID, City, Zip:\n");
    lookup_PNCZ(pncTable, "*", "J. Thomas", "*", "*");
/*
    PNCZ current = lookup_PNCZ(pncTable, "*", "J. Thomas", "*", "*");;
    while (current != NULL) {
        printf("PID = %s, Name = %s, City = %s, Zip = %s\n",
               get_PNCZ_pid(current), get_PNCZ_name(current),
               get_PNCZ_city(current), get_PNCZ_zip(current));
        current = get_PNCZ_next(current);  // Move to the next in list
    }
    */

    // Free the table after all operations are complete
    free_PNCZHashTable(pncTable);

    return 0;
}
