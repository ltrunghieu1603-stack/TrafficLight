#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdint.h>

#define NO_OF_BUTTONS 4

void button_reading(void);
uint8_t isButtonPressed(uint8_t index);
uint8_t isButtonPressed1s(uint8_t index);

#endif /* INC_BUTTON_H_ */
