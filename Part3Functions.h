#ifndef PART3FUNCTIONS_H
#define PART3FUNCTIONS_H

// ============================================
// (1) Selection Function Prototypes
// ============================================
RPTHashTable select_RPT_Race(RPTHashTable table, const char* race);

// ============================================
// (2) Projection Functions for projP (PId)
// ============================================
struct projP {
    int pid;
    struct projP* next;
};
typedef struct projP *projP;

struct projPHashTable {
    int size;
    projP* buckets;
    int count;
};
typedef struct projPHashTable *projPHashTable;

// Function Prototypes for projP
int hash_int(int pid, int size);
projP create_projP(int pid);
projPHashTable new_projPHashTable(int size);
void free_projPHashTable(projPHashTable table);
int get_projP_pid(projP entry);
void insert_projP(projPHashTable table, projP entry);
void print_projPTable(projPHashTable table);

projPHashTable proj_RPT_PId(RPTHashTable table, const char* race);

// ============================================
// (3) Structures and Functions for RDS (Join)
// ============================================
struct RDS {
    char race[50];
    char date[15];
    char sponsor[20];
    struct RDS* next;
};
typedef struct RDS *RDS;

struct RDSHashTable {
    int size;
    RDS* buckets;
    int count;
};
typedef struct RDSHashTable *RDSHashTable;

// Function Prototypes for RDS
int hash_race_date_sponsor(const char* race, const char* date, const char* sponsor, int table_size);
RDS create_RDS(const char* race, const char* date, const char* sponsor);
RDSHashTable new_RDSHashTable(int size);
void free_RDSHashTable(RDSHashTable table);
const char* get_RDS_race(RDS entry);
const char* get_RDS_date(RDS entry);
const char* get_RDS_sponsor(RDS entry);
void insert_RDS(RDSHashTable table, RDS entry);
void print_RDSHashTable(RDSHashTable table);

RDSHashTable join_RD_RS(RDHashTable rdTable, RSHashTable rsTable);

// ============================================
// (4) Projection Functions for projSp (Sponsor)
// ============================================
struct projSp {
    char sponsor[20];
    struct projSp* next;
};
typedef struct projSp *projSp;

struct projSpHashTable {
    int size;
    projSp* buckets;
    int count;
};
typedef struct projSpHashTable *projSpHashTable;

// Function Prototypes for projSp
RDSHashTable select_join_RD_RS_Date(RDHashTable table, RSHashTable, const char* date);
int hash_sponsor(const char* sponsor, int size);
projSp create_projSp(const char* sponsor);
projSpHashTable new_projSpHashTable(int size);
void free_projSpHashTable(projSpHashTable table);
const char* get_RS_sponsor(RS entry);
void insert_projSp(projSpHashTable table, projSp entry);
void print_projSpTable(projSpHashTable table);

projSpHashTable proj_RDS_Sp(RDSHashTable table);

#endif //PART3FUNCTIONS_H