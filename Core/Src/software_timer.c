#include "software_timer.h"

uint8_t timer_flag[MAX_TIMERS] = {0};
static uint32_t timer_counter[MAX_TIMERS] = {0};

void setTimer(uint8_t index, uint32_t duration_ms) {
    if (index >= MAX_TIMERS) return;
    timer_counter[index] = duration_ms / 10;
    timer_flag[index] = 0;
}

void timerRun(void) {
    for (uint8_t i = 0; i < MAX_TIMERS; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] == 0) {
                timer_flag[i] = 1;
            }
        }
    }
}
