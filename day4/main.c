#include <stdio.h>
#include <ctype.h>
#include "points.h"
#include "cards.h"

int main() {
    FILE *file_descriptor = fopen("./input.txt", "r");
    if (file_descriptor == NULL) {
        perror("fopen");

        return -1;
    }

    // Part 1
    // compute_total_points(file_descriptor);

    // Part 2
    compute_total_scratchcards(file_descriptor);

    fclose(file_descriptor);
}