#include "fileio.h"
#include <stdio.h>
#include <string.h>

/* Записывает массив структур Person в текстовый файл */
int write_persons_to_file(const char *filename, const Person arr[], int n) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;

    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n", arr[i].last_name);
        fprintf(f, "%s\n", arr[i].first_name);
        fprintf(f, "%s\n", arr[i].middle_name);
        fprintf(f, "%s\n", arr[i].gender);
        fprintf(f, "%s\n", arr[i].nationality);
        fprintf(f, "%.1f\n", arr[i].height);
        fprintf(f, "%.1f\n", arr[i].weight);
        fprintf(f, "%d %d %d\n",
                arr[i].birth.year,
                arr[i].birth.month,
                arr[i].birth.day);
        fprintf(f, "%s\n", arr[i].phone);
        fprintf(f, "%s\n", arr[i].address.postal_code);
        fprintf(f, "%s\n", arr[i].address.country);
        fprintf(f, "%s\n", arr[i].address.region);
        fprintf(f, "%s\n", arr[i].address.district);
        fprintf(f, "%s\n", arr[i].address.city);
        fprintf(f, "%s\n", arr[i].address.street);
        fprintf(f, "%d %d\n",
                arr[i].address.house,
                arr[i].address.apartment);
    }
    fclose(f);
    return 0;
}

/* Читает массив структур Person из текстового файла */
int read_persons_from_file(const char *filename, Person arr[], int max_n) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    int n = 0;
    fscanf(f, "%d\n", &n);
    if (n > max_n) n = max_n;

    for (int i = 0; i < n; i++) {
        fgets(arr[i].last_name,   MAX_STR, f);
        arr[i].last_name[strcspn(arr[i].last_name, "\n")] = 0;
        fgets(arr[i].first_name,  MAX_STR, f);
        arr[i].first_name[strcspn(arr[i].first_name, "\n")] = 0;
        fgets(arr[i].middle_name, MAX_STR, f);
        arr[i].middle_name[strcspn(arr[i].middle_name, "\n")] = 0;
        fgets(arr[i].gender,      16,      f);
        arr[i].gender[strcspn(arr[i].gender, "\n")] = 0;
        fgets(arr[i].nationality, MAX_STR, f);
        arr[i].nationality[strcspn(arr[i].nationality, "\n")] = 0;

        fscanf(f, "%f\n", &arr[i].height);
        fscanf(f, "%f\n", &arr[i].weight);
        fscanf(f, "%d %d %d\n",
               &arr[i].birth.year,
               &arr[i].birth.month,
               &arr[i].birth.day);

        fgets(arr[i].phone, 32, f);
        arr[i].phone[strcspn(arr[i].phone, "\n")] = 0;

        fgets(arr[i].address.postal_code, 16,      f);
        arr[i].address.postal_code[strcspn(arr[i].address.postal_code, "\n")] = 0;
        fgets(arr[i].address.country,     MAX_STR, f);
        arr[i].address.country[strcspn(arr[i].address.country, "\n")] = 0;
        fgets(arr[i].address.region,      MAX_STR, f);
        arr[i].address.region[strcspn(arr[i].address.region, "\n")] = 0;
        fgets(arr[i].address.district,    MAX_STR, f);
        arr[i].address.district[strcspn(arr[i].address.district, "\n")] = 0;
        fgets(arr[i].address.city,        MAX_STR, f);
        arr[i].address.city[strcspn(arr[i].address.city, "\n")] = 0;
        fgets(arr[i].address.street,      MAX_STR, f);
        arr[i].address.street[strcspn(arr[i].address.street, "\n")] = 0;
        fscanf(f, "%d %d\n",
               &arr[i].address.house,
               &arr[i].address.apartment);
    }
    fclose(f);
    return n;
}

/* Выводит содержимое файла на экран построчно */
void view_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open file: %s\n", filename);
        return;
    }
    char line[256];
    int  lineno = 1;
    while (fgets(line, sizeof(line), f)) {
        printf("%3d: %s", lineno++, line);
    }
    fclose(f);
}

/* Возвращает указатель на самого молодого человека */
const Person *find_youngest(const Person arr[], int n) {
    if (n <= 0) return NULL;
    const Person *youngest = &arr[0];
    for (int i = 1; i < n; i++) {
        const BirthDate *a = &arr[i].birth;
        const BirthDate *b = &youngest->birth;
        if (a->year > b->year ||
           (a->year == b->year && a->month > b->month) ||
           (a->year == b->year && a->month == b->month && a->day > b->day)) {
            youngest = &arr[i];
        }
    }
    return youngest;
}

/* Записывает данные самого молодого человека в файл */
void write_result_to_file(const char *filename, const Person *p) {
    FILE *f = fopen(filename, "w");
    if (!f) return;
    fprintf(f, "=== Youngest Person ===\n");
    fprintf(f, "Name:        %s %s %s\n",
            p->last_name, p->first_name, p->middle_name);
    fprintf(f, "Gender:      %s\n", p->gender);
    fprintf(f, "Nationality: %s\n", p->nationality);
    fprintf(f, "Height:      %.1f cm\n", p->height);
    fprintf(f, "Weight:      %.1f kg\n", p->weight);
    fprintf(f, "Birth:       %04d-%02d-%02d\n",
            p->birth.year, p->birth.month, p->birth.day);
    fprintf(f, "Phone:       %s\n", p->phone);
    fprintf(f, "Address:     %s, %s, %s, %s, %s, %s, %d/%d\n",
            p->address.postal_code,
            p->address.country,
            p->address.region,
            p->address.district,
            p->address.city,
            p->address.street,
            p->address.house,
            p->address.apartment);
    fclose(f);
}

/* Выводит данные человека на экран */
void print_person(const Person *p) {
    printf("  Name:        %s %s %s\n",
           p->last_name, p->first_name, p->middle_name);
    printf("  Gender:      %s\n", p->gender);
    printf("  Nationality: %s\n", p->nationality);
    printf("  Height:      %.1f cm\n", p->height);
    printf("  Weight:      %.1f kg\n", p->weight);
    printf("  Birth:       %04d-%02d-%02d\n",
           p->birth.year, p->birth.month, p->birth.day);
    printf("  Phone:       %s\n", p->phone);
    printf("  Address:     %s, %s, %s, %s, %s, %s, %d/%d\n",
           p->address.postal_code,
           p->address.country,
           p->address.region,
           p->address.district,
           p->address.city,
           p->address.street,
           p->address.house,
           p->address.apartment);
}
