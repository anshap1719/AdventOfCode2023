#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "contents.h"
#include "types.h"

void display_position(struct SymbolPosition* position) {
    printf("row: %zu, col: %zu\n", position->row, position->col);
}

void display_digit_position(struct DigitPosition* position) {
    printf("row: %zu, col: %zu, number: %ld\n", position->row, position->col, position->parsed_number);
}

bool are_positions_equal(struct SymbolPosition* left, struct SymbolPosition* right) {
    return left->row == right->row && left->col == right->col;
}

struct SymbolPositionCollection compute_digit_positions(struct SymbolPosition* symbol_positions, size_t count) {
    size_t digit_positions_count = count * 8;

    struct SymbolPosition* digit_positions = malloc(digit_positions_count * sizeof(struct SymbolPosition));

    for (size_t i = 0; i < digit_positions_count; i += 8) {
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

    for (size_t i = 0; i < digit_positions_count; i++) {
        for (size_t j = 0; j < digit_positions_count; j++) {
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
        printf("row: %zu, col: %zu\n", positions->positions[i].row, positions->positions[i].col);
    }
}

int main() {
    FILE *file_descriptor = fopen("./input.txt", "r");
    if (file_descriptor == NULL) {
        perror("fopen");

        return -1;
    }

    char character;

    size_t row = 0;
    size_t col = 0;

    size_t positions_count = 0;

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

    col--;

    rewind(file_descriptor);

    char (*contents)[row][col];
    struct SymbolPosition (*positions)[positions_count];

    positions = malloc(sizeof(struct SymbolPosition));
    alloc_contents_grid(row, col, &contents);
    read_contents_grid(file_descriptor, positions_count, *positions, row, col, *contents);

    fclose(file_descriptor);

    struct SymbolPositionCollection digit_positions = compute_digit_positions(*positions, positions_count);
    struct DigitPositionCollection number_positions = {
            .count = 0,
            .positions = malloc(digit_positions.count * sizeof(struct DigitPosition)),
    };

    free(positions);

    size_t number_position_index = 0;

    for(size_t i=0; i<row; i++)
    {
        for(size_t j=0; j<col; j++)
        {
            printf("%c", *contents[i][j]);
        }
        printf("\n");
    }

//    for (size_t i = 0; i < digit_positions.count; i++) {
//        struct SymbolPosition position = digit_positions.positions[i];
//
//        if (position.row < 0 || position.col < 0) {
//            continue;
//        }
//
//        char content = contents[position.row][position.col];
//
//        if (content == '.') {
//            continue;
//        }
//
//        if (isdigit(content)) {
//
//            size_t start_position = position.col;
//            size_t end_position = position.col + 1;
//            size_t digits_count = 0;
//
//            while (start_position >= 0 && isdigit(*contents[position.row][start_position]) && *contents[position.row][start_position] != '.') {
//                start_position--;
//                digits_count++;
//            }
//
//            start_position++;
//
//            while (isdigit(*contents[position.row][end_position]) && *contents[position.row][end_position] != '.') {
//                end_position++;
//                digits_count++;
//            }
//
//            struct DigitPosition digit_position;
//            digit_position.row = position.row;
//            digit_position.col = start_position;
//            digit_position.digits_count = digits_count;
//
//            char digit_string[digits_count];
//
//            for (size_t j = 0; j < digits_count; j++) {
//                digit_string[j] = *contents[position.row][start_position + j];
//            }
//
//            digit_position.parsed_number = strtol(digit_string, NULL, 10);
//            bool is_already_present = false;
//
//            for (size_t j = 0; j < number_positions.count; j++) {
//                if (number_positions.positions[j].row == digit_position.row && number_positions.positions[j].col == digit_position.col && digit_position.row != 0 && digit_position.col != 0) {
//                    is_already_present = true;
//                    break;
//                }
//            }
//
//            if (!is_already_present) {
//                number_positions.positions[number_position_index] = digit_position;
//                number_positions.count++;
//
//                number_position_index++;
//            }
//        }
//    }

    free(contents);
    free(digit_positions.positions);

//    size_t final_sum = 0;
//
//    for (size_t i = 0; i < number_positions.count; i++) {
//        display_digit_position(&number_positions.positions[i]);
//        final_sum += number_positions.positions[i].parsed_number;
//    }
//
//    printf("Numbers count: %ld\n", number_positions.count);
//    printf("Final sum: %ld\n", final_sum);

    free(number_positions.positions);
}