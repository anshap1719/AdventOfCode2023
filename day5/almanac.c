//
// Created by Anshul Sanghi on 03/01/24.
//

#include "almanac.h"
#include "types.h"

int64_t map_source_id(int64_t source_id, struct RangeMapDescriptorCollection* collection) {
    int64_t destination_id = source_id;

    for (int map_index = 0; map_index < collection->count; map_index++) {
        struct RangeMapDescriptor* entry = &collection->ranges[map_index];

        if (source_id >= entry->source_start && source_id <= entry->source_start + entry->range_count) {
            int64_t range_index = source_id - entry->source_start;
            destination_id = entry->destination_start + range_index;
            break;
        }
    }

    return destination_id;
}

int64_t find_lowest_location_for_almanac(struct Almanac* almanac) {
    int64_t lowest_location = -1;

    for (int seed_index = 0; seed_index < almanac->count; seed_index++) {
        int64_t seed_id = almanac->seeds[seed_index];

        int64_t soil_id = map_source_id(seed_id, &almanac->seed_to_soil_map);
        int64_t fertilizer_id = map_source_id(soil_id, &almanac->soil_to_fertilizer_map);
        int64_t water_id = map_source_id(fertilizer_id, &almanac->fertilizer_to_water_map);
        int64_t light_id = map_source_id(water_id, &almanac->water_to_light_map);
        int64_t temperature_id = map_source_id(light_id, &almanac->light_to_temperature_map);
        int64_t humidity_id = map_source_id(temperature_id, &almanac->temperature_to_humidity_map);
        int64_t location_id = map_source_id(humidity_id, &almanac->humidity_to_location_map);

        if (lowest_location == -1 || lowest_location > location_id) {
            lowest_location = location_id;
        }
    }

    return lowest_location;
}