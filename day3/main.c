#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "contents.h"
#include "types.h"
#include "engine_part.h"
#include "gear_ratio.h"

int main() {
    FILE *file_descriptor = fopen("./input.txt", "r");
    if (file_descriptor == NULL) {
        perror("fopen");

        return -1;
    }

    char character;

    int row = 0;
    int col = 0;

    int positions_count = 0;

    while ((character = fgetc(file_descriptor)) != EOF) {
        switch (character) {
            case '\n':
                row++;
                col = 0;
                continue;
            case '.':
                col++;
                continue;
            default:
                if (isdigit(character)) {
                    col++;
                    continue;
                } else {
                    positions_count++;
                    col++;
                    continue;
                }
        }
    }

    row++;

    rewind(file_descriptor);

    char ** contents = malloc(sizeof(char*) * row);

    for (int i = 0; i < row; i++) {
        contents[i] = malloc(sizeof(char) * col);
    }

    struct SymbolPosition *positions = malloc(sizeof(struct SymbolPosition) * positions_count);

    positions = malloc(sizeof(struct SymbolPosition));
    read_contents_grid(file_descriptor, positions_count, positions, contents);

    fclose(file_descriptor);

    compute_engine_parts_sum(positions_count, positions, contents);
    compute_gear_ratio_sum(positions_count, positions, contents);

    for (int i = 0; i < row; i++) {
        free(contents[i]);
    }

    free(contents);
    free(positions);
}