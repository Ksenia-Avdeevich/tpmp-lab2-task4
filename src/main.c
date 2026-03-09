#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

int main(int argc, char *argv[]) {
    const char *input  = "data/input.txt";
    const char *output = "data/output.txt";

    if (argc >= 2) input  = argv[1];
    if (argc >= 3) output = argv[2];

    /* Создать входной файл */
    if (create_file(input) != 0) {
        printf("Error creating file: %s\n", input);
        return 1;
    }
    printf("Input file: %s\n", input);
    view_file(input);

    /* Обработать и записать результат */
    if (process_file(input, output) != 0) {
        printf("Error processing file\n");
        return 1;
    }
    printf("\nOutput file: %s\n", output);
    view_file(output);

    return 0;
}
