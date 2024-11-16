#ifndef PART3FUNCTIONS_H
#define PART3FUNCTIONS_H

void select_RPT_Race(RPTHashTable rptTable, const char* race);
void project_RPT_PId(RPTHashTable rptTable, const char* race);
void join_RD_RS(RDHashTable rdTable, RSHashTable rsTable);
void query_project_sponsor_by_date(RDHashTable rdTable, RSHashTable rsTable, const char* target_date);



#endif