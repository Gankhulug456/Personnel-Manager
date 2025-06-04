// personnel.h
#ifndef PERSONNEL_H
#define PERSONNEL_H

typedef struct PERSONNEL_REC
{
    char *last_name;
    char *first_name;
    char middle_initial;
    int age;
    int salary;
    long id_type;
} PERSONNEL_REC;

void add_record(const char *last_name, const char *first_name, char middle_initial, int age, long id_type, int salary);

// Get records sorted by criteria.
// Returns a pointer to an array of PERSONNEL_REC pointers, sets *count to number of records.
// Caller must not free the array or records (managed internally)
PERSONNEL_REC **get_records_sorted_by_name(int *count);
PERSONNEL_REC **get_records_sorted_by_age(int *count);
PERSONNEL_REC **get_records_sorted_by_salary(int *count);
PERSONNEL_REC **get_records_sorted_by_id(int *count);

void free_all_records();

#endif
