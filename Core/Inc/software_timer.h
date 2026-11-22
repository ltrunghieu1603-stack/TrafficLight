#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>

#define MAX_TIMERS 5

extern uint8_t timer_flag[MAX_TIMERS];

void setTimer(uint8_t index, uint32_t duration_ms);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
