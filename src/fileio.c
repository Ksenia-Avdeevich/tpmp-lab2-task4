#include "fileio.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Создаёт файл с тестовыми данными */
int create_file(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;
    fprintf(f, "Hello World\n");
    fprintf(f, "Apple tree and orange juice\n");
    fprintf(f, "A cat sat on a mat\n");
    fprintf(f, "Beautiful day today\n");
    fclose(f);
    return 0;
}

/* Выводит содержимое файла на экран */
void view_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Cannot open file: %s\n", filename);
        return;
    }
    char line[256];
    int lineno = 1;
    while (fgets(line, sizeof(line), f)) {
        printf("%3d: %s", lineno++, line);
    }
    fclose(f);
}

/* Обрабатывает файл: считает слова и записывает результат */
int process_file(const char *src, const char *dst) {
    FILE *in  = fopen(src, "r");
    FILE *out = fopen(dst, "w");
    if (!in || !out) return -1;

    char line[256];
    int total_words = 0;
    int line_num = 1;

    while (fgets(line, sizeof(line), in)) {
        int words = 0;
        int in_word = 0;
        for (int i = 0; line[i]; i++) {
            if (!isspace((unsigned char)line[i])) {
                if (!in_word) { words++; in_word = 1; }
            } else { in_word = 0; }
        }
        total_words += words;
        fprintf(out, "Line %d: %d words | %s", line_num++, words, line);
    }
    fprintf(out, "\nTotal words: %d\n", total_words);
    fclose(in);
    fclose(out);
    return 0;
}
