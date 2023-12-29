#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct SymbolPosition {
    int row;
    int col;
};

struct SymbolPositionCollection {
    struct SymbolPosition* positions;
    long count;
};

struct DigitPosition {
    int row;
    int col;
    int digits_count;
    long parsed_number;
};

void display_position(struct SymbolPosition* position) {
    printf("row: %d, col: %d\n", position->row, position->col);
}

bool are_positions_equal(struct SymbolPosition* left, struct SymbolPosition* right) {
    return left->row == right->row && left->col == right->col;
}

struct SymbolPositionCollection compute_digit_positions(struct SymbolPosition* symbol_positions, int count) {
    long digit_positions_count = count * 8;

    struct SymbolPosition* digit_positions = malloc(digit_positions_count * sizeof(struct SymbolPosition));

    for (int i = 0; i < digit_positions_count; i += 8) {
        struct SymbolPosition position = symbol_positions[i / 8];

        digit_positions[i].row = position.row - 1;
        digit_positions[i].col = position.col;

        digit_positions[i + 1].row = position.row - 1;
        digit_positions[i + 1].col = position.col - 1;

        digit_positions[i + 2].row = position.row;
        digit_positions[i + 2].col = position.col - 1;

        digit_positions[i + 3].row = position.row + 1;
        digit_positions[i + 3].col = position.col;

        digit_positions[i + 4].row = position.row + 1;
        digit_positions[i + 4].col = position.col + 1;

        digit_positions[i + 5].row = position.row;
        digit_positions[i + 5].col = position.col + 1;

        digit_positions[i + 6].row = position.row - 1;
        digit_positions[i + 6].col = position.col + 1;

        digit_positions[i + 7].row = position.row + 1;
        digit_positions[i + 7].col = position.col - 1;
    }

    for (int i = 0; i < digit_positions_count; i++) {
        for (int j = 0; j < digit_positions_count; j++) {
            if (i != j && are_positions_equal(&digit_positions[j], &digit_positions[i])) {
                digit_positions[j].row = -1;
                digit_positions[j].col = -1;
            }
        }
    }

    struct SymbolPositionCollection result;
    result.positions = digit_positions;
    result.count = digit_positions_count;

    return result;
}

void display_positions(struct SymbolPositionCollection* positions) {
    for (long i = 0; i < positions->count; i++) {
        printf("row: %d, col: %d\n", positions->positions[i].row, positions->positions[i].col);
    }
}

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

    rewind(file_descriptor);

    char contents[row][col];

    struct SymbolPosition positions[positions_count];
    int index = 0;
    row = 0;
    col = 0;

    while ((character = fgetc(file_descriptor)) != EOF) {
        contents[row][col] = character;

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
                    positions[index].row = row;
                    positions[index].col = col;
                    index++;
                    col++;
                    continue;
                }
        }
    }

    fclose(file_descriptor);

    struct SymbolPositionCollection digit_positions = compute_digit_positions(positions, positions_count);

    for (int i = 0; i < digit_positions.count; i++) {
        struct SymbolPosition position = digit_positions.positions[i];

        if (position.row < 0 || position.col < 0) {
            continue;
        }

        char content = contents[position.row][position.col];

        if (content == '.') {
            continue;
        }

        if (isdigit(content)) {

            int start_position = position.col;
            int end_position = position.col + 1;
            int digits_count = 0;

            while (start_position >= 0 && isdigit(contents[position.row][start_position]) && contents[position.row][start_position] != '.') {
                start_position--;
                digits_count++;
            }

            start_position++;

            while (isdigit(contents[position.row][end_position]) && contents[position.row][end_position] != '.') {
                end_position++;
                digits_count++;
            }

            // TODO: Remove duplicate positions
            struct DigitPosition digit_position;
            digit_position.row = position.row;
            digit_position.col = start_position;
            digit_position.digits_count = digits_count;

            char digit_string[digits_count];

            for (int j = 0; j < digits_count; j++) {
                digit_string[j] = contents[position.row][start_position + j];
            }

            digit_position.parsed_number = strtol(digit_string, NULL, 10);
        }
    }

    free(digit_positions.positions);
}