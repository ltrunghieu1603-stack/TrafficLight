#ifndef INC_DHT20_H_
#define INC_DHT20_H_

#include "main.h"
#include <stdint.h>

#define DHT20_I2C_ADDR (0x38 << 1)

extern float dht20_temperature;
extern float dht20_humidity;

void dht20_init(I2C_HandleTypeDef *hi2c);
void dht20_task_update(void);

#endif /* INC_DHT20_H_ */
