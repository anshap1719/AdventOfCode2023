//
// Created by Anshul Sanghi on 03/01/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

int count_entries_for_label(char* line_copy, FILE* file_descriptor) {
    int count = 0;

    while (fgets(line_copy, 1024, file_descriptor) != NULL) {
        char *line_ctx;
        char* token;

        if (*line_copy == '\n') {
            break;
        }

        token = strtok_r(line_copy, " ", &line_ctx);
        if (isdigit(*token)) {
            count++;
        }
    }

    return count;
}

void populate_entries_for_label(char* line_copy, FILE* file_descriptor, struct RangeMapDescriptorCollection* collection) {
    int index = 0;

    while (fgets(line_copy, 1024, file_descriptor) != NULL) {
        char *line_ctx;
        char* token;

        if (*line_copy == '\n') {
            break;
        }

        struct RangeMapDescriptor range;

        token = strtok_r(line_copy, " ", &line_ctx);
        if (isdigit(*token)) {
            range.destination_start = (int64_t)strtoll(token, NULL, 10);
        }

        token = strtok_r(NULL, " ", &line_ctx);
        if (isdigit(*token)) {
            range.source_start = (int64_t)strtoll(token, NULL, 10);
        }

        token = strtok_r(NULL, " ", &line_ctx);
        if (isdigit(*token)) {
            range.range_count = (int64_t)strtoll(token, NULL, 10);
        }

        collection->ranges[index] = range;

        index++;
    }
}

void init_almanac(FILE* file_descriptor, struct Almanac* almanac) {
    char* line = malloc(sizeof(char) * 1024);

    int seed_count = 0;
    int seed_to_soil_map_count = 0;
    int soil_to_fertilizer_map_count = 0;
    int fertilizer_to_water_map_count = 0;
    int water_to_light_map_count = 0;
    int light_to_temperature_map_count = 0;
    int temperature_to_humidity_map_count = 0;
    int humidity_to_location_map_count = 0;

    while (fgets(line, 1024, file_descriptor) != NULL) {
        if (strncmp(line, "seeds", 5) == 0) {
            char *line_ctx;
            // Remove seeds label and ignore it
            strtok_r(line, ":", &line_ctx);

            char* token;

            while ((token = strtok_r(NULL, " ", &line_ctx)) != NULL) {
                if (isdigit(*token)) {
                    seed_count++;
                }
            }

            free(token);
            free(line_ctx);
        }

        if (strncmp(line, "seed-to-soil map", strlen("seed-to-soil map")) == 0) {
            seed_to_soil_map_count = count_entries_for_label(line, file_descriptor);
        }

        if (strncmp(line, "soil-to-fertilizer map", strlen("soil-to-fertilizer map")) == 0) {
            soil_to_fertilizer_map_count = count_entries_for_label(line, file_descriptor);
        }

        if (strncmp(line, "fertilizer-to-water map", strlen("fertilizer-to-water map")) == 0) {
            fertilizer_to_water_map_count = count_entries_for_label(line, file_descriptor);
        }

        if (strncmp(line, "water-to-light map", strlen("water-to-light map")) == 0) {
            water_to_light_map_count = count_entries_for_label(line, file_descriptor);
        }

        if (strncmp(line, "light-to-temperature map", strlen("light-to-temperature map")) == 0) {
            light_to_temperature_map_count = count_entries_for_label(line, file_descriptor);
        }

        if (strncmp(line, "temperature-to-humidity map", strlen("temperature-to-humidity map")) == 0) {
            temperature_to_humidity_map_count = count_entries_for_label(line, file_descriptor);
        }

        if (strncmp(line, "humidity-to-location map", strlen("humidity-to-location map")) == 0) {
            humidity_to_location_map_count = count_entries_for_label(line, file_descriptor);
        }
    }

    free(line);
    rewind(file_descriptor);

    almanac->count = seed_count;

    almanac->seed_to_soil_map.count = seed_to_soil_map_count;
    almanac->seed_to_soil_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * seed_to_soil_map_count);

    almanac->soil_to_fertilizer_map.count = soil_to_fertilizer_map_count;
    almanac->soil_to_fertilizer_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * soil_to_fertilizer_map_count);

    almanac->fertilizer_to_water_map.count = fertilizer_to_water_map_count;
    almanac->fertilizer_to_water_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * fertilizer_to_water_map_count);

    almanac->water_to_light_map.count = water_to_light_map_count;
    almanac->water_to_light_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * water_to_light_map_count);

    almanac->light_to_temperature_map.count = light_to_temperature_map_count;
    almanac->light_to_temperature_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * light_to_temperature_map_count);

    almanac->temperature_to_humidity_map.count = temperature_to_humidity_map_count;
    almanac->temperature_to_humidity_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * temperature_to_humidity_map_count);

    almanac->humidity_to_location_map.count = humidity_to_location_map_count;
    almanac->humidity_to_location_map.ranges = malloc(sizeof(struct RangeMapDescriptor) * humidity_to_location_map_count);

    almanac->seeds = malloc(sizeof(int64_t) * seed_count);
}

struct Almanac parse_input(FILE* file_descriptor) {
    struct Almanac almanac;

    init_almanac(file_descriptor, &almanac);

    char* line = malloc(sizeof(char) * 1024);
    int seed_index = 0;

    while (fgets(line, 1024, file_descriptor) != NULL) {
        if (strncmp(line, "seeds", 5) == 0) {
            char *line_ctx;
            // Remove seeds label and ignore it
            strtok_r(line, ":", &line_ctx);

            char* token;

            while ((token = strtok_r(NULL, " ", &line_ctx)) != NULL) {
                if (isdigit(*token)) {
                    almanac.seeds[seed_index] = (int64_t)strtoll(token, NULL, 10);
                    seed_index++;
                }
            }

            free(token);
            free(line_ctx);
        }

        if (strncmp(line, "seed-to-soil map", strlen("seed-to-soil map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.seed_to_soil_map);
        }

        if (strncmp(line, "soil-to-fertilizer map", strlen("soil-to-fertilizer map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.soil_to_fertilizer_map);
        }

        if (strncmp(line, "fertilizer-to-water map", strlen("fertilizer-to-water map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.fertilizer_to_water_map);
        }

        if (strncmp(line, "water-to-light map", strlen("water-to-light map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.water_to_light_map);
        }

        if (strncmp(line, "light-to-temperature map", strlen("light-to-temperature map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.light_to_temperature_map);
        }

        if (strncmp(line, "temperature-to-humidity map", strlen("temperature-to-humidity map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.temperature_to_humidity_map);
        }

        if (strncmp(line, "humidity-to-location map", strlen("humidity-to-location map")) == 0) {
            populate_entries_for_label(line, file_descriptor, &almanac.humidity_to_location_map);
        }
    }

    free(line);

    return almanac;
}