#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>
#include "software_timer.h"
#include "button.h"
#include "traffic_light.h"
#include "lcd.h"
#include "dht20.h"

#define INIT                0
#define AUTO_RED1_GREEN2    1
#define AUTO_RED1_AMBER2    2
#define AUTO_GREEN1_RED2    3
#define AUTO_AMBER1_RED2    4

#define MAN_INIT            10
#define MAN_RED1_GREEN2     11
#define MAN_GREEN1_RED2     12

#define TUN_INIT            20
#define TUN_RED             21
#define TUN_AMBER           22
#define TUN_GREEN           23

extern int status;
extern int time_red;
extern int time_amber;
extern int time_green;
extern int temp_time;

void lcd_display_system(void);

#endif /* INC_GLOBAL_H_ */
