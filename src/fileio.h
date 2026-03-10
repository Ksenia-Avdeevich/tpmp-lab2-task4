#ifndef FILEIO_H
#define FILEIO_H

#define MAX_STR     64
#define MAX_PERSONS 5

typedef struct {
    int year;
    int month;
    int day;
} BirthDate;

typedef struct {
    char postal_code[16];
    char country[MAX_STR];
    char region[MAX_STR];
    char district[MAX_STR];
    char city[MAX_STR];
    char street[MAX_STR];
    int  house;
    int  apartment;
} Address;

typedef struct {
    char      last_name[MAX_STR];
    char      first_name[MAX_STR];
    char      middle_name[MAX_STR];
    char      gender[16];
    char      nationality[MAX_STR];
    float     height;
    float     weight;
    BirthDate birth;
    char      phone[32];
    Address   address;
} Person;

int           write_persons_to_file(const char *filename, const Person arr[], int n);
int           read_persons_from_file(const char *filename, Person arr[], int max_n);
void          view_file(const char *filename);
const Person *find_youngest(const Person arr[], int n);
void          write_result_to_file(const char *filename, const Person *p);
void          print_person(const Person *p);

#endif /* FILEIO_H */
