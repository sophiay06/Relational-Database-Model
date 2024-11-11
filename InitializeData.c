#include "PNCZ.h"
#include "RPT.h"
#include "RD.h"
#include "RS.h"
#include "RQ.h"

void initialize_PNCZ_data(PNCZHashTable table) {
    insert_PNCZ(table, create_PNCZ(67815, "E. Allen", "Clarkson", 14642));
    insert_PNCZ(table, create_PNCZ(37435, "J. Thomas", "Churchville", 14643));
    insert_PNCZ(table, create_PNCZ(41222, "H. Evans", "North Gates", 14621));
    insert_PNCZ(table, create_PNCZ(31444, "E. Allen", "Pittsford", 14559));
    insert_PNCZ(table, create_PNCZ(89602, "J. Thomas", "Hamlin", 14651));
    insert_PNCZ(table, create_PNCZ(69441, "O. Price", "Hamlin", 14506));
}


void initialize_RPT_data(RPTHashTable table) {
    insert_RPT(table, create_RPT("UTri", 69441, "01:45:12"));
    insert_RPT(table, create_RPT("CSC Marathon",31444, "01:22:22"));
    insert_RPT(table, create_RPT("GVP Classic",89602, "01:52:26"));
    insert_RPT(table, create_RPT("CSC Marathon",67815, "00:32:32"));
    insert_RPT(table, create_RPT("Buffalo Stampede",41222, "01:53:57"));
    insert_RPT(table, create_RPT("GVP Classic",37435, "01:20:23"));
}


void initialize_RD_data(RDHashTable table) {
    insert_RD(table, create_RD("RocRace", "2023-07-27"));
    insert_RD(table, create_RD("Buffalo Stampede", "2023-05-16"));
    insert_RD(table, create_RD("UTri", "2023-11-02"));
    insert_RD(table, create_RD("GVP Classic", "2023-05-16"));
    insert_RD(table, create_RD("CSC Marathon", "2023-11-11"));
}


void initialize_RS_data(RSHashTable table) {
    insert_RS(table, create_RS("Buffalo Stampede", "Sadida"));
    insert_RS(table, create_RS("CSC Marathon", "Psyke"));
    insert_RS(table, create_RS("CSC Marathon", "URMC Ortho"));
    insert_RS(table, create_RS("GVP Classic", "LizardAde"));
    insert_RS(table, create_RS("Buffalo Stampede", "Run Club"));
    insert_RS(table, create_RS("RocRace", "Crooks"));

}


void initialize_RQ_data(RQHashTable table) {
    insert_RQ(table, create_RQ("RocRace", "Buffalo Stampede"));
    insert_RQ(table, create_RQ("GVP Classic", "CSC Marathon"));
    insert_RQ(table, create_RQ("GVP Classic", "RocRace"));
}