//
// Created by Anshul Sanghi on 02/01/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "points.h"
#include "card.h"

void compute_total_points(FILE* file_descriptor) {
    char* line = malloc(sizeof(char) * 1024);

    int points_total = 0;

    while (fgets(line, 1024, file_descriptor) != NULL) {
        struct Card* card = read_from_line(line);
        if (card == NULL) {
            continue;
        }

        int card_points = compute_matching_numbers_sum(card);

        points_total += card_points;

        free(card->card_numbers);
        free(card->winning_numbers);
        free(card);
    }

    free(line);
    rewind(file_descriptor);

    printf("Total points: %d", points_total);
}