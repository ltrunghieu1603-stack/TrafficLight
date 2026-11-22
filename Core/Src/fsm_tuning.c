	#include "fsm_tuning.h"

static uint8_t blink_state = 0;

static void blink_lights(LightColor_t color) {
    if (timer_flag[1] == 1) {
        blink_state = !blink_state;
        setTimer(1, 500);
    }
    if (blink_state) {
        traffic_set(1, color);
        traffic_set(2, color);
    } else {
        traffic_set(1, LIGHT_OFF);
        traffic_set(2, LIGHT_OFF);
    }
}

void fsm_tuning_run(void) {
    switch (status) {
        case TUN_INIT:
            temp_time = time_red;
            blink_state = 1;
            setTimer(1, 500);
            status = TUN_RED;
            break;

        case TUN_RED:
            blink_lights(LIGHT_RED);
            if (isButtonPressed(2)) {
                temp_time += 1000;
                if (temp_time > 99000) temp_time = 2000;
            }
            if (isButtonPressed(3)) {
                temp_time -= 1000;
                if (temp_time < 2000) temp_time = 99000;
            }
            if (isButtonPressed(1)) {
                time_red = temp_time;
                temp_time = time_amber;
                status = TUN_AMBER;
            }
            if (isButtonPressed(0)) {
                time_red = temp_time;
                if (time_red != time_green + time_amber) {
                    time_red = time_green + time_amber;
                }
                status = AUTO_RED1_GREEN2;
                setTimer(0, time_green);
            }
            break;

        case TUN_AMBER:
            blink_lights(LIGHT_AMBER);
            if (isButtonPressed(2)) {
                temp_time += 1000;
                if (temp_time > 99000) temp_time = 1000;
            }
            if (isButtonPressed(3)) {
                temp_time -= 1000;
                if (temp_time < 1000) temp_time = 99000;
            }
            if (isButtonPressed(1)) {
                time_amber = temp_time;
                temp_time = time_green;
                status = TUN_GREEN;
            }
            if (isButtonPressed(0)) {
                time_amber = temp_time;
                if (time_red != time_green + time_amber) {
                    time_red = time_green + time_amber;
                }
                status = AUTO_RED1_GREEN2;
                setTimer(0, time_green);
            }
            break;

        case TUN_GREEN:
            blink_lights(LIGHT_GREEN);
            if (isButtonPressed(2)) {
                temp_time += 1000;
                if (temp_time > 99000) temp_time = 1000;
            }
            if (isButtonPressed(3)) {
                temp_time -= 1000;
                if (temp_time < 1000) temp_time = 99000;
            }
            if (isButtonPressed(1)) {
                time_green = temp_time;
                temp_time = time_red;
                status = TUN_RED;
            }
            if (isButtonPressed(0)) {
                time_green = temp_time;
                if (time_red != time_green + time_amber) {
                    time_red = time_green + time_amber;
                }
                status = AUTO_RED1_GREEN2;
                setTimer(0, time_green);
            }
            break;

        default:
            break;
    }
}
