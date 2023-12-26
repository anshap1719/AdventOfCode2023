#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    FILE *file_descriptor = fopen("/Users/anshulsanghi/Developer/aoc2023/1-1/input.txt", "r");
    if (file_descriptor == NULL) {
        perror("fopen");

        return -1;
    }

    struct stat file_stat;
    stat("/Users/anshulsanghi/Developer/aoc2023/1-1/input.txt", &file_stat);

    char *contents = malloc(1024);

    int final_sum = 0;

    while (fgets(contents, 1024, file_descriptor) != NULL) {
        int character_index = 0;

        int first_digit = -1;
        int last_digit = -1;

        while (character_index < strlen(contents)) {
            char character = contents[character_index];
            char *end_pointer;

            int parsed_digit = -1;

            character_index++;

            if (character == '\n') {
                break;
            }

            if (isdigit(character)) {
                parsed_digit = (int) strtol(&character, &end_pointer, 10);
            } else {
                switch (character) {
                    case 'o':
                        if (strncmp("ne", &contents[character_index], 2) == 0) {
                            parsed_digit = 1;
                            break;
                        }
                    case 't':
                        if (strncmp("wo", &contents[character_index], 2) == 0) {
                            parsed_digit = 2;
                            break;
                        } else if (strncmp("hree", &contents[character_index], 4) == 0) {
                            parsed_digit = 3;
                            break;
                        }
                    case 'f':
                        if (strncmp("our", &contents[character_index], 3) == 0) {
                            parsed_digit = 4;
                            break;
                        } else if (strncmp("ive", &contents[character_index], 3) == 0) {
                            parsed_digit = 5;
                            break;
                        }
                    case 's':
                        if (strncmp("ix", &contents[character_index], 2) == 0) {
                            parsed_digit = 6;
                            break;
                        } else if (strncmp("even", &contents[character_index], 4) == 0) {
                            parsed_digit = 7;
                            break;
                        }
                    case 'e':
                        if (strncmp("ight", &contents[character_index], 4) == 0) {
                            parsed_digit = 8;
                            break;
                        }
                    case 'n':
                        if (strncmp("ine", &contents[character_index], 3) == 0) {
                            parsed_digit = 9;
                            break;
                        }
                    case 'z':
                        if (strncmp("ero", &contents[character_index], 3) == 0) {
                            parsed_digit = 0;
                            break;
                        }
                }
            }

            if (parsed_digit != -1) {
                if (first_digit == -1) {
                    first_digit = parsed_digit;
                }

                last_digit = parsed_digit;
            }
        }

        printf("first: %d | last: %d | character: %s\n", first_digit, last_digit, contents);

        if (first_digit == -1 || last_digit == -1) {
            printf("Failed to get first and last digits\n");
            return -1;
        }

        char final_number[3] = {0};

        sprintf(final_number, "%d%d", first_digit, last_digit);
        char *ptr;

        int final_digits = (int) strtol(final_number, &ptr, 10);

        final_sum += final_digits;
    }

    free(contents);
    fclose(file_descriptor);

    printf("The sum of all calibration value is: %d\n", final_sum);

    return 0;
}