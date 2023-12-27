#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define GENERIC_MAX(x, y) ((x) > (y) ? (x) : (y))

#define ENSURE_int(i)   _Generic((i), int:   (i))
#define ENSURE_float(f) _Generic((f), float: (f))

#define MAX(type, x, y) \
  (type)GENERIC_MAX(ENSURE_##type(x), ENSURE_##type(y))

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;

enum Color {
    Red = 0,
    Green = 1,
    Blue = 2,
};

struct Draw {
    int count;
    enum Color color;
};

typedef struct {
    struct Draw draws[3];
} set_draws;

struct Set {
    set_draws draws;
};

struct Game {
    int id;
    struct Set sets[10];
    bool is_valid;
};

struct Draw create_draw_from_string(char* draw) {
    char draw_copy[20] = {};

    strcpy(draw_copy, draw);

    char* ctx;

    char* numbers = strtok_r(draw_copy, " ", &ctx);
    char* color = strtok_r(NULL, "\0", &ctx);

    struct Draw draw_st = {};

    draw_st.count = (int) strtol(numbers, NULL, 10);

    if (strncmp(color, "red", 3) == 0) {
        draw_st.color = Red;
    }

    if (strncmp(color, "green", 5) == 0) {
        draw_st.color = Green;
    }

    if (strncmp(color, "blue", 4) == 0) {
        draw_st.color = Blue;
    }

    return draw_st;
}

bool verify_draw(struct Draw* draw) {
    if (draw->color == Red) {
        return draw->count <= MAX_RED;
    }

    if (draw->color == Green) {
        return draw->count <= MAX_GREEN;
    }

    if (draw->color == Blue) {
        return draw->count <= MAX_BLUE;
    }

    return false;
}

int find_minimum_cubes_power(struct Game* game) {
    int minimum_red = 1;
    int minimum_green = 1;
    int minimum_blue = 1;

    for (int set_index = 0; set_index < 10; set_index++) {
        set_draws draws = game->sets[set_index].draws;

        for (int draw_index = 0; draw_index < 3; draw_index++) {
            struct Draw draw = draws.draws[draw_index];
            switch(draw.color) {
                case Red:
                    minimum_red = MAX(int, minimum_red, draw.count);
                    continue;
                case Green:
                    minimum_green = MAX(int, minimum_green, draw.count);
                    continue;
                case Blue:
                    minimum_blue = MAX(int, minimum_blue, draw.count);
                    continue;
            }
        }
    }

    return minimum_red * minimum_green * minimum_blue;
}

int main() {
    FILE *file_descriptor = fopen("./input.txt", "r");
    if (file_descriptor == NULL) {
        perror("fopen");

        return -1;
    }

    char *game = malloc(4096);

    int valid_id_sum = 0;
    int min_power_sum = 0;

    while (fgets(game, 1024, file_descriptor) != NULL) {
        if (strncmp(game, "Game ", 5) != 0) {
            return 1;
        }

        char *game_ctx;

        char *game_id_token = strtok_r(&game[5], ":", &game_ctx);
        int game_id = (int)strtol(game_id_token, NULL, 10);

        struct Game game_info = {
            .id =  game_id,
            .sets =  {},
            .is_valid = true,
        };

        char *set;

        char* sets[10] = {NULL};

        int set_index = 0;

        while ((set = strtok_r(NULL, ";", &game_ctx)) != NULL) {
            sets[set_index] = set;
            set_index++;
        }

        set_index = 0;

        for (int i=0; i < 10; i++) {
            if (sets[i] != NULL) {
                struct Set game_sets = {};
                char set_info[200] = {};

                strcpy(set_info, sets[i]);

                char* ctx;

                char *draw = strtok_r(set_info, ",", &ctx);
                game_sets.draws.draws[0] = create_draw_from_string(draw);
                game_info.is_valid = game_info.is_valid && verify_draw(&game_sets.draws.draws[0]);

                draw = strtok_r(NULL, ",", &ctx);
                if (draw != NULL) {
                    game_sets.draws.draws[1] = create_draw_from_string(draw);
                    game_info.is_valid = game_info.is_valid && verify_draw(&game_sets.draws.draws[1]);
                } else {
                    game_info.sets[set_index] = game_sets;
                    set_index++;
                    continue;
                }

                draw = strtok_r(NULL, ",", &ctx);
                if (draw != NULL) {
                    game_sets.draws.draws[2] = create_draw_from_string(draw);
                    game_info.is_valid = game_info.is_valid && verify_draw(&game_sets.draws.draws[2]);
                } else {
                    game_info.sets[set_index] = game_sets;
                    set_index++;
                    continue;
                }

                game_info.sets[set_index] = game_sets;
            }

            set_index++;
        }

        if (game_info.is_valid) {
            valid_id_sum += game_info.id;
        }

        min_power_sum += find_minimum_cubes_power(&game_info);
    }

    free(game);
    fclose(file_descriptor);

    printf("Final sum is %d\n", valid_id_sum);
    printf("Final power is %d\n", min_power_sum);

    return 0;
}