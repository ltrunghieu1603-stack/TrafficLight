#include "fsm_manual.h"

void fsm_manual_run(void) {
    switch (status) {
        case MAN_INIT:
            status = MAN_RED1_GREEN2;
            break;

        case MAN_RED1_GREEN2:
            traffic_set(1, LIGHT_RED);
            traffic_set(2, LIGHT_GREEN);
            if (isButtonPressed(1)) {
                status = MAN_GREEN1_RED2;
            }
            if (isButtonPressed(0)) {
                status = TUN_INIT;
            }
            break;

        case MAN_GREEN1_RED2:
            traffic_set(1, LIGHT_GREEN);
            traffic_set(2, LIGHT_RED);
            if (isButtonPressed(1)) {
                status = MAN_RED1_GREEN2;
            }
            if (isButtonPressed(0)) {
                status = TUN_INIT;
            }
            break;

        default:
            break;
    }
}
