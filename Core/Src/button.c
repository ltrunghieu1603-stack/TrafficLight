#include "button.h"

#define TIMER_CYCLE 10
#define DURATION_FOR_AUTO_INCREASING (1000 / TIMER_CYCLE)
#define BUTTON_IS_PRESSED  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};
static GPIO_PinState prevButtonBuffer[NO_OF_BUTTONS] = {
    BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED
};

static uint8_t flagForButtonPress[NO_OF_BUTTONS] = {0};
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS] = {0};
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS] = {0};

static GPIO_TypeDef* buttonPort[NO_OF_BUTTONS] = {
    BTN_0_GPIO_Port, BTN_1_GPIO_Port, BTN_2_GPIO_Port, BTN_3_GPIO_Port
};
static uint16_t buttonPin[NO_OF_BUTTONS] = {
    BTN_0_Pin, BTN_1_Pin, BTN_2_Pin, BTN_3_Pin
};

void button_reading(void) {
    for (uint8_t i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i];
        }

        if (buttonBuffer[i] != prevButtonBuffer[i]) {
            prevButtonBuffer[i] = buttonBuffer[i];
            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                flagForButtonPress[i] = 1;
            }
        }

        if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
            if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                counterForButtonPress1s[i]++;
            } else {
                flagForButtonPress1s[i] = 1;
            }
        } else {
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
    }
}

uint8_t isButtonPressed(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    if (flagForButtonPress[index] == 1) {
        flagForButtonPress[index] = 0;
        return 1;
    }
    return 0;
}

uint8_t isButtonPressed1s(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    return (flagForButtonPress1s[index] == 1);
}
