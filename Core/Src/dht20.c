#include "dht20.h"

static I2C_HandleTypeDef *dht_i2c;
static uint8_t dht_state = 0;

float dht20_temperature = 0.0f;
float dht20_humidity = 0.0f;

void dht20_init(I2C_HandleTypeDef *hi2c) {
    dht_i2c = hi2c;
    dht_state = 0;
}

void dht20_task_update(void) {
    if (dht_i2c == NULL) return;

    if (dht_state == 0) {
        uint8_t cmd[3] = {0xAC, 0x33, 0x00};
        if (HAL_I2C_Master_Transmit(dht_i2c, DHT20_I2C_ADDR, cmd, 3, 50) == HAL_OK) {
            dht_state = 1;
        }
    } else {
        uint8_t data[7] = {0};
        if (HAL_I2C_Master_Receive(dht_i2c, DHT20_I2C_ADDR, data, 7, 50) == HAL_OK) {
            if ((data[0] & 0x80) == 0) {
                uint32_t raw_humi = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
                uint32_t raw_temp = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];

                dht20_humidity = (raw_humi * 100.0f) / 1048576.0f;
                dht20_temperature = ((raw_temp * 200.0f) / 1048576.0f) - 50.0f;
            }
        }
        dht_state = 0;
    }
}
