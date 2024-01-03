#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "almanac.h"

int main() {
    FILE *file_descriptor = fopen("./input.txt", "r");
    if (file_descriptor == NULL) {
        perror("fopen");

        return -1;
    }

    struct Almanac almanac = parse_input(file_descriptor);
    display_almanac(&almanac);

    int64_t lowest_location = find_lowest_location_for_almanac(&almanac);

    printf("Lowest Location: %lld\n", lowest_location);

    free(almanac.seeds);
    free(almanac.seed_to_soil_map.ranges);
    free(almanac.soil_to_fertilizer_map.ranges);
    free(almanac.fertilizer_to_water_map.ranges);
    free(almanac.water_to_light_map.ranges);
    free(almanac.light_to_temperature_map.ranges);
    free(almanac.temperature_to_humidity_map.ranges);
    free(almanac.humidity_to_location_map.ranges);
}
