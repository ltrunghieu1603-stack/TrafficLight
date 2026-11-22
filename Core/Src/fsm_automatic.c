#include "fsm_automatic.h"

void fsm_automatic_run(void) {
    switch (status) {
        case INIT:
            traffic_set(1, LIGHT_OFF);
            traffic_set(2, LIGHT_OFF);
            status = AUTO_RED1_GREEN2;
            setTimer(0, time_green);
            break;

        case AUTO_RED1_GREEN2:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_GREEN);
            if (timer_flag[0] == 1) {
                status = AUTO_RED1_AMBER2;
                setTimer(0, time_amber);
            }
            if (isButtonPressed(0)) {
                status = MAN_INIT;
            }
            break;

        case AUTO_RED1_AMBER2:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_AMBER);
            if (timer_flag[0] == 1) {
                status = AUTO_GREEN1_RED2;
                setTimer(0, time_green);
            }
            if (isButtonPressed(0)) {
                status = MAN_INIT;
            }
            break;

        case AUTO_GREEN1_RED2:
            traffic_set(1, LIGHT_GREEN);
            traffic_set(2, LIGHT_RED);
            if (timer_flag[0] == 1) {
                status = AUTO_AMBER1_RED2;
                setTimer(0, time_amber);
            }
            if (isButtonPressed(0)) {
                status = MAN_INIT;
            }
            break;

        case AUTO_AMBER1_RED2:
            traffic_set(1, LIGHT_AMBER);
            traffic_set(2, LIGHT_RED);
            if (timer_flag[0] == 1) {
                status = AUTO_RED1_GREEN2;
                setTimer(0, time_green);
            }
            if (isButtonPressed(0)) {
                status = MAN_INIT;
            }
            break;

        default:
            break;
    }
}
