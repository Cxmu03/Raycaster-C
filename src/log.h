#ifndef RAYCASTING_LOG_H
#define RAYCASTING_LOG_H

#include <stdio.h>

#define STR(x)       #x
#define STR_MACRO(x) STR(x)
#define INFO(...)    printf("[INFO] " __VA_ARGS__)
#define BEEP_BEEP_FEHLER_ERKANNT(...)                                                                                  \
    fprintf(stderr, "[BEEP_BEEP_FEHLER_ERKANNT] in file " __FILE__ " line " STR_MACRO(__LINE__) "\n" __VA_ARGS__)

#endif // RAYCASTING_LOG_H
