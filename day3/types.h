//
// Created by Anshul Sanghi on 31/12/23.
//

#ifndef DAY3_TYPES_H
#define DAY3_TYPES_H

struct SymbolPosition {
    int row;
    int col;
};

struct SymbolPositionCollection {
    struct SymbolPosition* positions;
    int count;
};

struct DigitPosition {
    int row;
    int col;
    int digits_count;
    int parsed_number;
};

struct DigitPositionCollection {
    struct DigitPosition* positions;
    int count;
};

#endif //DAY3_TYPES_H
