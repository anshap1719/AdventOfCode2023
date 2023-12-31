#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "types.h"

void alloc_contents_grid(size_t x, size_t y, char(**contents)[x][y]) {
    *contents = malloc(sizeof(char[x][y]));
    if (*contents == NULL) {
        perror("malloc");
    }
}

void read_contents_grid(FILE* file_descriptor, size_t positions_count, struct SymbolPosition positions[positions_count], size_t rows, size_t columns, char contents[rows][columns]) {
    char character;

    size_t row = 0;
    size_t col = 0;
    size_t index = 0;

    while ((character = fgetc(file_descriptor)) != EOF) {
        switch (character) {
            case '\n':
                row++;
                col = 0;
                continue;
            case '.':
                contents[row][col] = character;
                col++;
                continue;
            default:
                contents[row][col] = character;
                if (isdigit(character)) {
                    col++;
                    continue;
                } else {
                    positions[index].row = row;
                    positions[index].col = col;
                    index++;
                    col++;
                    continue;
                }
        }
    }
}
