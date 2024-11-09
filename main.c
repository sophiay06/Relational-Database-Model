#include <stdio.h>
#include "PNCZ.h"
#include "RPT.h"

void initialize_PNCZ_data(PNCZHashTable table) {
    printf("\nInitializing PNCZ database with initial data:\n");

    insert_PNCZ(table, create_PNCZ(67815, "E. Allen", "Clarkson", 14642));
    insert_PNCZ(table, create_PNCZ(37435, "J. Thomas", "Churchville", 14643));
    insert_PNCZ(table, create_PNCZ(41222, "H. Evans", "North Gates", 14621));
    insert_PNCZ(table, create_PNCZ(31444, "E. Allen", "Pittsford", 14559));
    insert_PNCZ(table, create_PNCZ(89602, "J. Thomas", "Hamlin", 14651));
    insert_PNCZ(table, create_PNCZ(69441, "O. Price", "Hamlin", 14506));

    print_PNCZTable(table);
}


void initialize_RPT_data(RPTHashTable table) {
    printf("\nInitializing RPT database with initial data:\n");

    insert_RPT(table, create_RPT("UTri", 69441, "01:45:12"));
    insert_RPT(table, create_RPT("CSC Marathon",31444, "01:22:22"));
    insert_RPT(table, create_RPT("GVP Classic",89602, "01:52:26"));
    insert_RPT(table, create_RPT("CSC Marathon",67815, "00:32:32"));
    insert_RPT(table, create_RPT("Buffalo Stampede",41222, "01:53:57"));
    insert_RPT(table, create_RPT("GVP Classic",37435, "01:20:23"));

    print_RPTTable(table);
}
int main() {
    int PNCZ_tableSize = 10;
    PNCZHashTable PNCZ_Table = new_PNCZHashTable(PNCZ_tableSize);
    if (PNCZ_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }
    initialize_PNCZ_data(PNCZ_Table);
    printf("\nDemonstrating operations:\n");
    printf("Lookup for entries with Name 'J. Thomas' and any PID, City, Zip:\n");
    lookup_PNCZ(PNCZ_Table, -1, "J. Thomas", "*", -1);
    printf("Delete the entries with Name 'J. Thomas' and any PID, City, Zip:\n");
    delete_PNCZ(PNCZ_Table, -1, "J. Thomas", "*", -1);

    int RPT_tableSize = 10;
    RPTHashTable RPT_Table = new_RPTHashTable(RPT_tableSize);
    if (RPT_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }
    initialize_RPT_data(RPT_Table);
    printf("\nDemonstrating operations:\n");
    printf("Lookup for entries with Race 'UTri' and any PID and Time:\n");
    lookup_RPT(RPT_Table, "UTri", -1, "*");
    printf("Delete the entries with Race 'UTri' and any PID and Time:\n");
    delete_RPT(RPT_Table, "UTri", -1, "*");

    // Free the table after all operations are complete
    free_PNCZHashTable(PNCZ_Table);
    free_RPTHashTable(RPT_Table);

    return 0;
}
