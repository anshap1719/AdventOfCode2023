//
// Created by Anshul Sanghi on 01/01/24.
//

#ifndef DAY3_CARD_H
#define DAY3_CARD_H

#include "types.h"

struct NumberCounts {
    int winning;
    int my;
};

void display_card(struct Card* card);

struct Card* clone_card(struct Card* card);

struct Card* read_from_line(char* line);

int compute_matching_numbers_sum(struct Card* card);

int compute_matching_numbers_count(struct Card* card);

#endif //DAY3_CARD_H
