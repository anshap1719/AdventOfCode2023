//
// Created by Anshul Sanghi on 01/01/24.
//

#ifndef DAY3_POSITION_H
#define DAY3_POSITION_H

#include <stdbool.h>
#include "types.h"

void display_position(struct SymbolPosition *position);

void display_digit_position(struct DigitPosition *position);

void display_digit_position_collection(struct DigitPositionCollection *positions);

bool are_positions_equal(struct SymbolPosition *left, struct SymbolPosition *right);

bool are_digit_positions_equal(struct DigitPosition *left, struct DigitPosition *right);

struct SymbolPositionCollection compute_digit_positions(struct SymbolPosition *symbol_positions, int count);

void display_positions(struct SymbolPositionCollection *positions);

#endif //DAY3_POSITION_H
