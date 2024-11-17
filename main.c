#include <stdio.h>
#include <string.h>
#include "PNCZ.h"
#include "RPT.h"
#include "RD.h"
#include "RS.h"
#include "RQ.h"
#include "InitializeData.h"
#include "Part2Functions.h"
#include "Part3Functions.h"

void part1() {
    //Creating hash tables for each database
    PNCZHashTable PNCZ_Table = new_PNCZHashTable(11);
    RPTHashTable RPT_Table = new_RPTHashTable(11);
    RDHashTable RD_Table = new_RDHashTable(11);
    RSHashTable RS_Table = new_RSHashTable(11);
    RQHashTable RQ_Table = new_RQHashTable(11);
    if (PNCZ_Table == NULL|| RPT_Table == NULL || RD_Table == NULL || RS_Table == NULL || RQ_Table == NULL) {
        fprintf(stderr, "Failed to create hash table.\n");
    }

    //Initializing data
    initialize_PNCZ_data(PNCZ_Table);
    printf("\nInitializing PNCZ database with initial data:\n");
    print_PNCZTable(PNCZ_Table);

    initialize_RPT_data(RPT_Table);
    printf("\nInitializing RPT database with initial data:\n");
    print_RPTTable(RPT_Table);

    initialize_RD_data(RD_Table);
    printf("\nInitializing RD database with initial data:\n");
    print_RDTable(RD_Table);

    initialize_RS_data(RS_Table);
    printf("\nInitializing RS database with initial data:\n");
    print_RSTable(RS_Table);

    initialize_RQ_data(RQ_Table);
    printf("\nInitializing RQ database with initial data:\n");
    print_RQTable(RQ_Table);

    printf("\nPart 1 Demonstration:\n");
    printf("\na: Lookup for entries with Race 'CSC Marathon', PID '67815', and any Time:\n");
    lookup_RPT(RPT_Table, "CSC Marathon", 67815, "*");
    printf("\nb: Lookup for entries with Name 'J. Thomas' and any PID, City, Zip:\n");
    lookup_PNCZ(PNCZ_Table, -1, "J. Thomas", "*", -1);
    printf("\nc: Lookup for entries with Race 'CSC Marathon' and Qualifier 'GVP Classic':\n");
    lookup_RQ(RQ_Table, "CSC Marathon", "GVP Classic");
    printf("\nd: Delete the entries with Race 'UTri' and Date 2023-11-02':\n");
    delete_RD(RD_Table, "UTri", "2023-11-02");
    printf("\ne: Delete the entries with Race 'GVP Classic' and Sponsor 'McDavid's':\n");
    delete_RS(RS_Table, "GVP Classic", "McDavid's");
    printf("\nf: Delete the entries with Sponsor 'LizardAde' and any Race:\n");
    delete_RS(RS_Table, "*", "LizardAde");
    printf("\ng: Insert the entry with Race 'GVP Classic' and Qualifier 'Newbie Classic':\n");
    insert_RQ(RQ_Table, create_RQ("GVP Classic", "Newbie Classic"));
    print_RQTable(RQ_Table);
    printf("\nh: Insert the entry with Race 'GVP Classic' and Qualifier 'CSC Marathon':\n");
    insert_RQ(RQ_Table, create_RQ("GVP Classic", "CSC Marathon"));
    print_RQTable(RQ_Table);

    // Free the table after all operations are complete
    free_PNCZHashTable(PNCZ_Table);
    free_RPTHashTable(RPT_Table);
    free_RDHashTable(RD_Table);
    free_RSHashTable(RS_Table);
    free_RQHashTable(RQ_Table);
}

void part2() {
    char name[50];
    char race[50];
    char sponsor[50];

    printf("\nPart 2 Demonstration:\n");

    printf("a: What time did Name get in Race?\n");
    while (1) {
        printf("\nEnter Name (or 'quit' to exit): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if (strcmp(name, "quit") == 0) break;

        printf("Enter Race (or 'quit' to exit): ");
        fgets(race, sizeof(race), stdin);
        race[strcspn(race, "\n")] = '\0';
        if (strcmp(race, "quit") == 0) break;

        query_time_in_race(name, race);
    }

    printf("\nb: On what date(s) did Name run a race sponsored by Sponsor?\n");
    while (1) {
        printf("\nEnter Name (or 'quit' to exit): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';
        if (strcmp(name, "quit") == 0) break;

        printf("Enter Sponsor (or 'quit' to exit): ");
        fgets(sponsor, sizeof(sponsor), stdin);
        sponsor[strcspn(sponsor, "\n")] = '\0';
        if (strcmp(sponsor, "quit") == 0) break;

        query_dates_by_name_and_sponsor(name, sponsor);
    }
}


void part3() {
    printf("\nPart 3 Demonstration:\n");

    printf("\n1: Selection: Select Race = 'GVP Classic' (RPT) \n");

    RPTHashTable rptTable= new_RPTHashTable(11);
    initialize_RPT_data(rptTable);

    print_RPTTable(select_RPT_Race(rptTable, "GVP Classic"));

    printf("\n2: Projection: Project PId ( Select Race = 'GVP Classic' (RPT) ) \n");

    print_projPTable(proj_RPT_PId(rptTable, "GVP Classic"));

    printf("\n3: Join RD and RS \n");

    RDHashTable rdTable1 = new_RDHashTable(11);
    initialize_RD_data(rdTable1);
    RSHashTable rsTable1 = new_RSHashTable(11);
    initialize_RS_data(rsTable1);

    print_RDSHashTable(join_RD_RS(rdTable1, rsTable1));

    printf("\n4: Project Sponsor(Select Date='2023-10-02'(RD join RS)) \n");

    RDHashTable rdTable2 = new_RDHashTable(11);
    initialize_RD_data(rdTable2);
    RSHashTable rsTable2 = new_RSHashTable(11);
    initialize_RS_data(rsTable2);

    print_projSpTable(proj_RDS_Sp(select_join_RD_RS_Date(rdTable2,rsTable2,"2023-10-02")));

    free_RPTHashTable(rptTable);
    free_RDHashTable(rdTable1);
    free_RSHashTable(rsTable1);
    free_RDHashTable(rdTable2);
    free_RSHashTable(rsTable2);
}

int main() {
    part1();
    part2();
    part3();
    return 0;
}
