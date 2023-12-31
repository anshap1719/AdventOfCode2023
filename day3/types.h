//
// Created by Anshul Sanghi on 31/12/23.
//

#ifndef DAY3_TYPES_H
#define DAY3_TYPES_H

struct SymbolPosition {
    size_t row;
    size_t col;
};

struct SymbolPositionCollection {
    struct SymbolPosition* positions;
    size_t count;
};

struct DigitPosition {
    size_t row;
    size_t col;
    size_t digits_count;
    size_t parsed_number;
};

struct DigitPositionCollection {
    struct DigitPosition* positions;
    size_t count;
};

#endif //DAY3_TYPES_H
