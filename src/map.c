#include "map.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "file_reader.h"
#include "log.h"

#define LINE_BUFFER_SIZE        255
#define INITIAL_MAP_BUFFER_SIZE (LINE_BUFFER_SIZE * LINE_BUFFER_SIZE)

/*size_t count_occurrences(const char* str, char delim) {
    char c;
    size_t occurrences = 0;
    while((c = *str++) != '\0') {
        occurrences += (c == delim);
    }
    return occurrences;
}

int* split(const char* str, char delim, size_t* size) {
    size_t occurences = count_occurrences(str, delim);
    int* data = calloc(occurences + 1, sizeof(int));

}*/

static inline size_t read_row(char* mapData, size_t offset, uint8_t** data) {
    size_t i = 0;
    for(; mapData[offset + i] != '\n'; i++) {}
    return i;
}

map_t* read_map(const char* filename) {
    map_t* map = calloc(1, sizeof(map_t));
    char* contents;
    size_t contentSize;
    if(read_file(filename, &contents, &contentSize) != READALL_INVALID) {
        BEEP_BEEP_FEHLER_ERKANNT("Failed to read file\n");
    }

    return map;
}

map_t* reaad_map(const char* filename) {
    FILE* mapFile = fopen(filename, "r");
    char* buffer = calloc(LINE_BUFFER_SIZE, sizeof(char));
    uint8_t* mapBuffer = calloc(INITIAL_MAP_BUFFER_SIZE, sizeof(uint8_t));
    map_t* map = calloc(1, sizeof(map_t));
    size_t countedBytes = 0;

    while(fgets(buffer, LINE_BUFFER_SIZE, mapFile) != NULL) {
        size_t lineSize = 0;
        size_t i = 0;
        for(; *(buffer + i) != '\n'; i++, lineSize++) {
            mapBuffer[countedBytes + lineSize] = *buffer - 48;
        }
        countedBytes += lineSize;
        map->width = lineSize;
    }
    map->height = countedBytes / map->width;

    void* reallocBuffer = realloc(mapBuffer, countedBytes);
    if(reallocBuffer == NULL) { BEEP_BEEP_FEHLER_ERKANNT("Could not reallocate buffer"); }
    mapBuffer = reallocBuffer;

    map->data = mapBuffer;

    return map;
}

inline uint8_t get_map_at(map_t* map, size_t x, size_t y) {
    return *(map->data + (y * map->width + x));
}