#include <stdio.h>
#include <ctype.h>
#include "types.h"

void read_contents_grid(FILE* file_descriptor, int positions_count, struct SymbolPosition positions[positions_count], char ** contents) {
    char character;

    int row = 0;
    int col = 0;
    int index = 0;

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
