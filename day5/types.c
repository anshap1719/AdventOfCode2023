//
// Created by Anshul Sanghi on 03/01/24.
//

#include <printf.h>
#include "types.h"

void display_almanac(struct Almanac* almanac) {
    printf("Seeds:\n");
    for (int i = 0; i < almanac->count; i++) {
        printf("\t%lld\n", almanac->seeds[i]);
    }

    printf("seed-to-soil map:\n");
    for (int i = 0; i < almanac->seed_to_soil_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->seed_to_soil_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }

    printf("soil-to-fertilizer map:\n");
    for (int i = 0; i < almanac->soil_to_fertilizer_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->soil_to_fertilizer_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }

    printf("fertilizer-to-water map:\n");
    for (int i = 0; i < almanac->fertilizer_to_water_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->fertilizer_to_water_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }

    printf("water-to-light map:\n");
    for (int i = 0; i < almanac->water_to_light_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->water_to_light_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }

    printf("light-to-temperature map:\n");
    for (int i = 0; i < almanac->light_to_temperature_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->light_to_temperature_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }

    printf("temperature-to-humidity map:\n");
    for (int i = 0; i < almanac->temperature_to_humidity_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->temperature_to_humidity_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }

    printf("humidity-to-location map:\n");
    for (int i = 0; i < almanac->humidity_to_location_map.count; i++) {
        struct RangeMapDescriptor* range = &almanac->humidity_to_location_map.ranges[i];
        printf("\t%lld | %lld | %lld\n", range->destination_start, range->source_start, range->range_count);
    }
}