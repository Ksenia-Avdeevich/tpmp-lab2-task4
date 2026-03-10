#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

int main(void) {
    const char *input_file  = "data/persons.txt";
    const char *output_file = "data/result.txt";

    /* Тестовые данные: 5 человек */
    Person people[MAX_PERSONS] = {
        {
            "Ivanov", "Ivan", "Ivanovich",
            "Male", "Russian", 178.0f, 75.0f,
            {1990, 5, 15}, "+375-29-000-00-01",
            {"220000", "Belarus", "Minsk region", "Minsk district",
             "Minsk", "Lenina", 1, 10}
        },
        {
            "Petrov", "Petr", "Petrovich",
            "Male", "Russian", 182.0f, 80.0f,
            {2002, 3, 22}, "+375-29-000-00-02",
            {"220001", "Belarus", "Minsk region", "Minsk district",
             "Minsk", "Mira", 5, 20}
        },
        {
            "Sidorova", "Anna", "Ivanovna",
            "Female", "Belarusian", 165.0f, 55.0f,
            {1998, 11, 1}, "+375-29-000-00-03",
            {"220002", "Belarus", "Grodno region", "Grodno district",
             "Grodno", "Pobedy", 3, 7}
        },
        {
            "Kovalev", "Dmitry", "Sergeevich",
            "Male", "Russian", 175.0f, 70.0f,
            {1985, 7, 30}, "+375-29-000-00-04",
            {"220003", "Belarus", "Brest region", "Brest district",
             "Brest", "Sovetskaya", 12, 45}
        },
        {
            "Morozova", "Elena", "Alexeevna",
            "Female", "Belarusian", 168.0f, 60.0f,
            {2004, 1, 8}, "+375-29-000-00-05",
            {"220004", "Belarus", "Vitebsk region", "Vitebsk district",
             "Vitebsk", "Zamkovaya", 7, 3}
        }
    };

    /* создать входной файл */
    printf("Step 1: Writing persons to file: %s\n", input_file);
    if (write_persons_to_file(input_file, people, MAX_PERSONS) != 0) {
        printf("Error: cannot write to file %s\n", input_file);
        return 1;
    }
    printf("Done.\n\n");

    /* просмотр содержимого файла*/
    printf("Step 2: Contents of %s\n", input_file);
    view_file(input_file);
    printf("\n");

    /* читать файл и обработать данные*/
    printf("Step 3: Reading persons from file\n");
    Person loaded[MAX_PERSONS];
    int n = read_persons_from_file(input_file, loaded, MAX_PERSONS);
    if (n < 0) {
        printf("Error: cannot read file %s\n", input_file);
        return 1;
    }
    printf("Read %d persons.\n\n", n);

    /* найти самого молодого*/
    printf(" Step 4: Finding youngest person\n");
    const Person *youngest = find_youngest(loaded, n);
    if (youngest) {
        print_person(youngest);
    }
    printf("\n");

    /* аписать результат в новый файл*/
    printf("Step 5: Saving result to %\n", output_file);
    if (youngest) {
        write_result_to_file(output_file, youngest);
        printf("Done. Result file contents:\n\n");
        view_file(output_file);
    }

    return 0;
}
