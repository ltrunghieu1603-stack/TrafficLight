#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

#include "main.h"
#include <stdint.h>

typedef enum {
    LIGHT_OFF = 0,
    LIGHT_RED,
    LIGHT_AMBER,
    LIGHT_GREEN
} LightColor_t;

void traffic_set(uint8_t lane, LightColor_t color);

#endif /* INC_TRAFFIC_LIGHT_H_ */
