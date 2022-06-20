#ifndef RAYCASTING_COLOR_HASH_MAP_H
#define RAYCASTING_COLOR_HASH_MAP_H

#include <stdint.h>

#include "color.h"
#include "util.h"

typedef struct KVP {
    uint64_t key;
    uint64_t hash;
    color_t value;
} kvp;

typedef struct BUCKET {
    uint8_t usedSlots;
    kvp pairs[5];
} bucket;

typedef struct COLOR_HASH_MAP {
    size_t capacity;
    kvp* pairs;
} color_hash_map;

color_hash_map* hash_map_create();
void hash_map_insert(uint64_t key, color_t value);
bool hashmap_contains(uint64_t key);
color_t hashmap_at(uint64_t);

#endif // RAYCASTING_COLOR_HASH_MAP_H
