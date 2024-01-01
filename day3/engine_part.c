#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "types.h"
#include "position.h"

void compute_engine_parts_sum(int positions_count, struct SymbolPosition *positions, char ** contents) {
    struct SymbolPositionCollection digit_positions = compute_digit_positions(positions, positions_count);
    struct DigitPositionCollection number_positions = {
            .count = 0,
            .positions = malloc(digit_positions.count * sizeof(struct DigitPosition)),
    };

    int number_position_index = 0;

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

            struct DigitPosition digit_position;
            digit_position.row = position.row;
            digit_position.col = start_position;
            digit_position.digits_count = digits_count;

            char digit_string[digits_count];

            for (int j = 0; j < digits_count; j++) {
                digit_string[j] = contents[position.row][start_position + j];
            }

            digit_position.parsed_number = strtol(digit_string, NULL, 10);
            bool is_already_present = false;

            for (int j = 0; j < number_positions.count; j++) {
                if (are_digit_positions_equal(&number_positions.positions[j], &digit_position)) {
                    is_already_present = true;
                    break;
                }
            }

            if (!is_already_present) {
                number_positions.positions[number_position_index] = digit_position;
                number_positions.count++;

                number_position_index++;
            }
        }
    }

    free(digit_positions.positions);

    int final_sum = 0;

    for (int i = 0; i < number_positions.count; i++) {
        final_sum += number_positions.positions[i].parsed_number;
    }

    printf("Computing Engine Parts...\n");
    printf("Numbers count: %d\n", number_positions.count);
    printf("Final sum: %d\n", final_sum);

    free(number_positions.positions);
}