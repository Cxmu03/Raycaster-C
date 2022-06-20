#ifndef RAYCASTING_UTIL_H
#define RAYCASTING_UTIL_H

#define PI        3.1415926535f
#define PI_HALVES 1.570796326f
#define TWO_PI    6.2831853071f

#define ARR_SIZE(a) = (sizeof(a) / sizeof((a)[0]))

typedef enum BOOL { false = 0, true = !false } bool;

static inline float
map_to(float value, float valueRangeMin, float valueRangeMax, float resultRangeMin, float resultRangeMax) {
    return resultRangeMin +
           (((value - valueRangeMin) / (valueRangeMax - valueRangeMin) * (resultRangeMax - resultRangeMin)));
}

static inline float deg_to_rad(float deg) {
    return (deg * PI) / 180.f;
}

static inline float rad_to_deg(float rad) {
    return (rad * 180.f) / PI;
}

#endif // RAYCASTING_UTIL_H
