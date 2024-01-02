//
// Created by Anshul Sanghi on 02/01/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "card.h"

struct Card* get_card_from_collection_by_id(struct CardCollection* collection, int id) {
    for (int i = 0; i < collection->count; i++) {
        if (collection->cards[i]->id == id) {
            return collection->cards[i];
        }
    }

    return NULL;
}

void compute_winning_cards_for_scratchcard(struct CardCollection* collection, struct Card* card) {
    int matching_numbers_count = compute_matching_numbers_count(card);
    int i = card->id + 1;
    int iteration_limit = i + matching_numbers_count;

    for (i; i < iteration_limit; i++) {
        struct Card* target_card = get_card_from_collection_by_id(collection, i);
        if (target_card == NULL) {
            continue;
        }

        struct Card* cloned_card = clone_card(target_card);

        collection->cards[collection->count] = cloned_card;
        collection->count++;

        compute_winning_cards_for_scratchcard(collection, cloned_card);
    }
}

void compute_total_scratchcards(FILE* file_descriptor) {
    char* line = malloc(sizeof(char) * 1024);

    struct CardCollection cards = {
        .count = 0,
        // TODO: Figure out a way to optimize this
        .cards = malloc(sizeof(struct Card*) * 20000)
    };

    int card_index = 0;

    while (fgets(line, 1024, file_descriptor) != NULL) {
        struct Card* card = read_from_line(line);
        if (card == NULL) {
            continue;
        }

        cards.count++;
        cards.cards[card_index] = card;

        card_index++;
    }

    free(line);
    rewind(file_descriptor);

    int loop_count = cards.count;

    for (int i = 0; i < loop_count; i++) {
        compute_winning_cards_for_scratchcard(&cards, cards.cards[i]);
    }

    printf("Total cards: %d", cards.count);

    for (int i = 0; i < cards.count; i++) {
        free(cards.cards[i]->card_numbers);
        free(cards.cards[i]->winning_numbers);
        free(cards.cards[i]);
    }

    free(cards.cards);
}