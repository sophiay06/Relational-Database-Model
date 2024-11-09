#include <stdio.h>
#include "PNCZ.h"
#include "RPT.h"
#include "RD.h"
#include "RS.h"
#include "RQ.h"

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

void initialize_RD_data(RDHashTable table) {
    printf("\nInitializing RD database with initial data:\n");

    insert_RD(table, create_RD("RocRace", "2023-07-27"));
    insert_RD(table, create_RD("Buffalo Stampede", "2023-05-16"));
    insert_RD(table, create_RD("UTri", "2023-11-02"));
    insert_RD(table, create_RD("GVP Classic", "2023-05-16"));
    insert_RD(table, create_RD("CSC Marathon", "2023-11-11"));

    print_RDTable(table);
}

void initialize_RS_data(RSHashTable table) {
    printf("\nInitializing RS database with initial data:\n");

    insert_RS(table, create_RS("Buffalo Stampede", "Sadida"));
    insert_RS(table, create_RS("CSC Marathon", "Psyke"));
    insert_RS(table, create_RS("CSC Marathon", "URMC Ortho"));
    insert_RS(table, create_RS("GVP Classic", "LizardAde"));
    insert_RS(table, create_RS("Buffalo Stampede", "Run Club"));
    insert_RS(table, create_RS("RocRace", "Crooks"));

    print_RSTable(table);
}

void initialize_RQ_data(RQHashTable table) {
    printf("\nInitializing RQ database with initial data:\n");

    insert_RQ(table, create_RQ("RocRace", "Buffalo Stampede"));
    insert_RQ(table, create_RQ("GVP Classic", "CSC Marathon"));
    insert_RQ(table, create_RQ("GVP Classic", "RocRace"));

    print_RQTable(table);
}

int main() {
    //PNCZ database
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

    //RPT database
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

    //RD database
    int RD_tableSize = 10;
    RDHashTable RD_Table = new_RDHashTable(RD_tableSize);
    if (RD_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }
    initialize_RD_data(RD_Table);
    printf("\nDemonstrating operations:\n");
    printf("Lookup for entries with Race 'RocRace' and any Date:\n");
    lookup_RD(RD_Table, "RocRace", "*");
    printf("Delete the entries with Race 'UTri' and Date '2023-11-02':\n");
    delete_RD(RD_Table, "UTri", "2023-11-02");

    //RS database
    int RS_tableSize = 7;
    RSHashTable RS_Table = new_RSHashTable(RS_tableSize);
    if (RS_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }
    initialize_RS_data(RS_Table);
    printf("\nDemonstrating operations:\n");
    printf("Lookup for entries with Race 'RocRace' and any Sponsor:\n");
    lookup_RS(RS_Table, "RocRace", "*");
    printf("Delete the entries with Race 'GVP Classic' and Sponsor 'McDavid's':\n");
    delete_RS(RS_Table, "GVP Classic", "McDavid's");
    printf("Delete the entries with Sponsor 'LizardAde' and any Race:\n");
    delete_RS(RS_Table, "*", "LizardAde");

    //RQ database
    int RQ_tableSize = 4;
    RQHashTable RQ_Table = new_RQHashTable(RQ_tableSize);
    if (RQ_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }
    initialize_RQ_data(RQ_Table);
    printf("\nDemonstrating operations:\n");
    printf("Lookup for entries with Race 'CSC Marathon' and Qualifier 'URMC Ortho':\n");
    lookup_RQ(RQ_Table, "CSC Marathon", "URMC Ortho");
    printf("Delete the entries with Race 'CSC Marathon' and any Qualifier:\n");
    delete_RQ(RQ_Table, "GVP Classic", "*");
    printf("Insert\n");
    insert_RQ(RQ_Table, create_RQ("GVP Classic", "Newbie Classic"));
    print_RQTable(RQ_Table);

    // Free the table after all operations are complete
    free_PNCZHashTable(PNCZ_Table);
    free_RPTHashTable(RPT_Table);
    free_RDHashTable(RD_Table);
    free_RSHashTable(RS_Table);
    free_RQHashTable(RQ_Table);

    return 0;
}
