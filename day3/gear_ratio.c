//
// Created by Anshul Sanghi on 01/01/24.
//

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "position.h"

void compute_gear_ratio_sum(int positions_count, struct SymbolPosition *positions, char ** contents) {
    struct SymbolPosition potential_gear_positions[positions_count];
    int gears_count = 0;

    for (int i = 0; i < positions_count; i++) {
        struct SymbolPosition* position = &positions[i];
        if (position->is_gear) {
            potential_gear_positions[gears_count].row = position->row;
            potential_gear_positions[gears_count].col = position->col;
            potential_gear_positions[gears_count].is_gear = true;

            gears_count++;
        }
    }

    struct SymbolPosition gear_positions[gears_count];

    memcpy(gear_positions, potential_gear_positions, sizeof(struct SymbolPosition) * gears_count);

    struct SymbolPositionCollection digit_positions = compute_digit_positions(gear_positions, gears_count);

    int final_sum = 0;

    for (int p = 0; p < digit_positions.count; p += 8) {
        struct DigitPositionCollection number_positions = {
                .count = 0,
                .positions = malloc(8 * sizeof(struct DigitPosition)),
        };

        int number_position_index = 0;

        struct SymbolPosition *position_pairs = malloc(8 * sizeof(struct SymbolPosition));
        memcpy(position_pairs, digit_positions.positions + p, sizeof(struct SymbolPosition) * 8);

        for (int i = 0; i < 8; i++) {
            struct SymbolPosition position = position_pairs[i];

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

        free(position_pairs);

        if (number_positions.count != 2) {
            free(number_positions.positions);
            continue;
        } else {
            final_sum += (number_positions.positions[0].parsed_number * number_positions.positions[1].parsed_number);
            free(number_positions.positions);
        }
    }

    free(digit_positions.positions);

    printf("\nComputing Gear Ratios...\n");
    printf("Final sum: %d\n", final_sum);
}
