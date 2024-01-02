//
// Created by Anshul Sanghi on 01/01/24.
//

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <printf.h>
#include "types.h"
#include "card.h"

struct Card* clone_card(struct Card* card) {
    struct Card* cloned_card = malloc(sizeof(struct Card));

    cloned_card->winning_numbers_count = card->winning_numbers_count;
    cloned_card->card_numbers_count = card->card_numbers_count;
    cloned_card->id = card->id;
    cloned_card->winning_numbers = malloc(sizeof(int) * card->winning_numbers_count);
    cloned_card->card_numbers = malloc(sizeof(int) * card->card_numbers_count);

    memcpy(cloned_card->winning_numbers, card->winning_numbers, sizeof(int) * card->winning_numbers_count);
    memcpy(cloned_card->card_numbers, card->card_numbers, sizeof(int) * card->card_numbers_count);

    return cloned_card;
}

void display_card(struct Card* card) {
    printf("Card %d\n", card->id);
    printf("\tWinning Numbers Count: %d\n", card->winning_numbers_count);

    for (int i = 0; i < card->winning_numbers_count; i++) {
        printf("\t\t%d\n", card->winning_numbers[i]);
    }

    printf("\tMy Numbers Count: %d\n", card->card_numbers_count);

    for (int i = 0; i < card->card_numbers_count; i++) {
        printf("\t\t%d\n", card->card_numbers[i]);
    }
}

struct NumberCounts compute_number_counts(char* line) {
    char *line_copy = malloc(sizeof(char) * strlen(line));
    strcpy(line_copy, line);

    char *card_ctx;

    int winning_numbers_count = 0;
    int my_numbers_count = 0;

    bool is_my_number = false;

    while ((strtok_r(line_copy, "|", &card_ctx)) != NULL) {
        if (is_my_number) {
            while ((strtok_r(NULL, " ", &line_copy)) != NULL) {
                winning_numbers_count++;
            }
        } else {
            is_my_number = true;
            while ((strtok_r(NULL, " ", &card_ctx)) != NULL) {
                my_numbers_count++;
            }
        }
    }

    free(line_copy);
    free(card_ctx);

    struct NumberCounts counts = {
            .my = my_numbers_count,
            .winning = winning_numbers_count,
    };

    return counts;
}

void populate_card_numbers(struct Card* card, char* line) {
    char *line_copy = malloc(sizeof(char) * strlen(line));
    strcpy(line_copy, line);

    char *card_ctx;

    int winning_numbers_index = 0;
    int my_numbers_index = 0;

    bool is_my_number = false;

    char* token;

    while ((strtok_r(line_copy, "|", &card_ctx)) != NULL) {
        if (is_my_number) {
            while ((token = strtok_r(NULL, " ", &line_copy)) != NULL) {
                if (isdigit(*token)) {
                    card->winning_numbers[winning_numbers_index] = (int) strtol(token, NULL, 10);
                    winning_numbers_index++;
                }
            }
        } else {
            is_my_number = true;
            while ((token = strtok_r(NULL, " ", &card_ctx)) != NULL) {
                if (isdigit(*token)) {
                    card->card_numbers[my_numbers_index] = (int) strtol(token, NULL, 10);
                    my_numbers_index++;
                }
            }
        }
    }

    free(line_copy);
    free(card_ctx);
    free(token);
}

struct Card* read_from_line(char* line) {
    if (strncmp(line, "Card ", 5) != 0) {
        return NULL;
    }

    char *card_ctx;

    char *card_id_token = strtok_r(&line[5], ":", &card_ctx);
    int card_id = (int)strtol(card_id_token, NULL, 10);

    char *line_copy = malloc(sizeof(char) * strlen(card_ctx));
    strcpy(line_copy, card_ctx);

    struct NumberCounts counts = compute_number_counts(card_ctx);

    struct Card *card = malloc(sizeof(struct Card));
    card->id = card_id;
    card->card_numbers = malloc(sizeof(int) * counts.my);
    card->winning_numbers = malloc(sizeof(int) * counts.winning);
    card->winning_numbers_count = counts.winning;
    card->card_numbers_count = counts.my;

    populate_card_numbers(card, line_copy);

    free(line_copy);

    return card;
}

int compute_matching_numbers_sum(struct Card* card) {
    int sum = 0;

    for (int i = 0; i < card->winning_numbers_count; i++) {
        int winning_number = card->winning_numbers[i];

        for (int j = 0; j < card->card_numbers_count; j++) {
            int my_number = card->card_numbers[j];

            if (winning_number == my_number) {
                if (sum == 0) {
                    sum = 1;
                } else {
                    sum = sum * 2;
                }
            }
        }
    }

    return sum;
}

int compute_matching_numbers_count(struct Card* card) {
    int sum = 0;

    for (int i = 0; i < card->winning_numbers_count; i++) {
        int winning_number = card->winning_numbers[i];

        for (int j = 0; j < card->card_numbers_count; j++) {
            int my_number = card->card_numbers[j];

            if (winning_number == my_number) {
                sum++;
            }
        }
    }

    return sum;
}