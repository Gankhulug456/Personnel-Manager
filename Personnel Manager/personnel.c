#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnel.h"

typedef struct NODE
{
    PERSONNEL_REC *record;
    struct NODE *left, *right;
} NODE;

static NODE *name_root = NULL;
static NODE *age_root = NULL;
static NODE *id_num_root = NULL;
static NODE *salary_root = NULL;

static PERSONNEL_REC **record_array = NULL;
static int record_count = 0;

static int compare_id_number(PERSONNEL_REC *p1, PERSONNEL_REC *p2)
{
    if (p1->id_type > p2->id_type)
        return 1;
    else if (p1->id_type < p2->id_type)
        return -1;
    else
        return 0;
}

static int compare_name(PERSONNEL_REC *p1, PERSONNEL_REC *p2)
{
    int result = strcmp(p1->last_name, p2->last_name);
    if (result != 0)
        return result;
    result = strcmp(p1->first_name, p2->first_name);
    if (result != 0)
        return result;
    if (p1->middle_initial > p2->middle_initial)
        return 1;
    if (p1->middle_initial < p2->middle_initial)
        return -1;
    return compare_id_number(p1, p2);
}

static int compare_age(PERSONNEL_REC *p1, PERSONNEL_REC *p2)
{
    if (p1->age > p2->age)
        return 1;
    else if (p1->age < p2->age)
        return -1;
    return compare_name(p1, p2);
}

static int compare_salary(PERSONNEL_REC *p1, PERSONNEL_REC *p2)
{
    if (p1->salary > p2->salary)
        return 1;
    else if (p1->salary < p2->salary)
        return -1;
    return compare_name(p1, p2);
}

// Create new record, copy strings safely
static PERSONNEL_REC *new_record(const char *last_name, const char *first_name, char middle_initial, int age, long id_type, int salary)
{
    PERSONNEL_REC *p = malloc(sizeof(PERSONNEL_REC));
    p->last_name = malloc(strlen(last_name) + 1);
    strcpy(p->last_name, last_name);
    p->first_name = malloc(strlen(first_name) + 1);
    strcpy(p->first_name, first_name);
    p->middle_initial = middle_initial;
    p->age = age;
    p->id_type = id_type;
    p->salary = salary;
    return p;
}

// Insert into BST
static void insert_personnel_record(NODE **root, PERSONNEL_REC *p, int (*compare)(PERSONNEL_REC *, PERSONNEL_REC *))
{
    if (*root == NULL)
    {
        NODE *new_node = malloc(sizeof(NODE));
        new_node->record = p;
        new_node->left = new_node->right = NULL;
        *root = new_node;
        return;
    }
    int cmp = compare(p, (*root)->record);
    if (cmp < 0)
        insert_personnel_record(&(*root)->left, p, compare);
    else if (cmp > 0)
        insert_personnel_record(&(*root)->right, p, compare);
    else
    {
        }
}

// Count nodes in tree
static int count_nodes(NODE *root)
{
    if (!root)
        return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Fill array by inorder traversal
static void fill_array_inorder(NODE *root, PERSONNEL_REC **arr, int *index)
{
    if (!root)
        return;
    fill_array_inorder(root->left, arr, index);
    arr[*index] = root->record;
    (*index)++;
    fill_array_inorder(root->right, arr, index);
}

// Free all nodes recursively
static void free_tree(NODE *root)
{
    if (!root)
        return;
    free_tree(root->left);
    free_tree(root->right);
    // Free record strings & record
    free(root->record->last_name);
    free(root->record->first_name);
    free(root->record);
    free(root);
}

void add_record(const char *last_name, const char *first_name, char middle_initial, int age, long id_type, int salary)
{
    PERSONNEL_REC *p = new_record(last_name, first_name, middle_initial, age, id_type, salary);
    insert_personnel_record(&name_root, p, compare_name);
    insert_personnel_record(&age_root, p, compare_age);
    insert_personnel_record(&id_num_root, p, compare_id_number);
    insert_personnel_record(&salary_root, p, compare_salary);
}

static PERSONNEL_REC **get_sorted_array(NODE *root, int *count)
{
    if (record_array)
    {
        free(record_array);
        record_array = NULL;
        record_count = 0;
    }
    record_count = count_nodes(root);
    *count = record_count;
    if (record_count == 0)
        return NULL;

    record_array = malloc(sizeof(PERSONNEL_REC *) * record_count);
    int index = 0;
    fill_array_inorder(root, record_array, &index);
    return record_array;
}

PERSONNEL_REC **get_records_sorted_by_name(int *count)
{
    return get_sorted_array(name_root, count);
}

PERSONNEL_REC **get_records_sorted_by_age(int *count)
{
    return get_sorted_array(age_root, count);
}

PERSONNEL_REC **get_records_sorted_by_salary(int *count)
{
    return get_sorted_array(salary_root, count);
}

PERSONNEL_REC **get_records_sorted_by_id(int *count)
{
    return get_sorted_array(id_num_root, count);
}

void free_all_records()
{
    free_tree(name_root);
    name_root = NULL;
    age_root = NULL;
    id_num_root = NULL;
    salary_root = NULL;
    if (record_array)
    {
        free(record_array);
        record_array = NULL;
        record_count = 0;
    }
}
