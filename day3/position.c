//
// Created by Anshul Sanghi on 01/01/24.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


void display_position(struct SymbolPosition *position) {
    printf("row: %d, col: %d\n", position->row, position->col);
}

void display_digit_position(struct DigitPosition *position) {
    printf("row: %d, col: %d, number: %d\n", position->row, position->col, position->parsed_number);
}

void display_digit_position_collection(struct DigitPositionCollection *positions) {
    for (int i = 0; i < positions->count; i++) {
        struct DigitPosition *position = &positions->positions[i];
        printf("row: %d, col: %d, number: %d\n", position->row, position->col, position->parsed_number);   
    }
}

bool are_positions_equal(struct SymbolPosition *left, struct SymbolPosition *right) {
    return left->row == right->row && left->col == right->col;
}

bool are_digit_positions_equal(struct DigitPosition *left, struct DigitPosition *right) {
    return left->row == right->row && left->col == right->col;
}

struct SymbolPositionCollection compute_digit_positions(struct SymbolPosition *symbol_positions, int count) {
    int digit_positions_count = count * 8;

    struct SymbolPosition *digit_positions = malloc(digit_positions_count * sizeof(struct SymbolPosition));

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

    struct SymbolPositionCollection result = {
            .count = digit_positions_count,
            .positions = malloc(digit_positions_count * sizeof(struct SymbolPosition))
    };

    memcpy(result.positions, digit_positions, digit_positions_count * sizeof(struct SymbolPosition));
    free(digit_positions);

    result.count = digit_positions_count;

    return result;
}

void display_positions(struct SymbolPositionCollection *positions) {
    for (int i = 0; i < positions->count; i++) {
        printf("row: %d, col: %d\n", positions->positions[i].row, positions->positions[i].col);
    }
}