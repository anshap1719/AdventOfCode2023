//
// Created by Anshul Sanghi on 03/01/24.
//

#ifndef DAY5_TYPES_H
#define DAY5_TYPES_H

#include <stdint.h>

struct RangeMapDescriptor {
    int64_t destination_start;
    int64_t source_start;
    int64_t range_count;
};

struct RangeMapDescriptorCollection {
    int64_t count;
    struct RangeMapDescriptor* ranges;
};

struct Almanac {
    int count;
    struct RangeMapDescriptorCollection seed_to_soil_map;
    struct RangeMapDescriptorCollection soil_to_fertilizer_map;
    struct RangeMapDescriptorCollection fertilizer_to_water_map;
    struct RangeMapDescriptorCollection water_to_light_map;
    struct RangeMapDescriptorCollection light_to_temperature_map;
    struct RangeMapDescriptorCollection temperature_to_humidity_map;
    struct RangeMapDescriptorCollection humidity_to_location_map;
    int64_t* seeds;
};

void display_almanac(struct Almanac* almanac);

#endif //DAY5_TYPES_H
