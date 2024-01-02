//
// Created by Anshul Sanghi on 01/01/24.
//

#ifndef DAY4_TYPES_H
#define DAY4_TYPES_H

struct Card {
    int id;
    int winning_numbers_count;
    int card_numbers_count;
    int* winning_numbers;
    int* card_numbers;
};

struct CardCollection {
    struct Card** cards;
    int count;
};

#endif //DAY4_TYPES_H
