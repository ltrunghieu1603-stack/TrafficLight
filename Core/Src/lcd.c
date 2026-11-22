#include "lcd.h"
#include <stdio.h>

static I2C_HandleTypeDef *lcd_i2c;

static void lcd_send_cmd(char cmd) {
    char data_u = (cmd & 0xF0);
    char data_l = ((cmd << 4) & 0xF0);
    uint8_t data_t[4];
    data_t[0] = data_u | 0x0C; // en=1, rs=0
    data_t[1] = data_u | 0x08; // en=0, rs=0
    data_t[2] = data_l | 0x0C; // en=1, rs=0
    data_t[3] = data_l | 0x08; // en=0, rs=0
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, data_t, 4, 50);
}

static void lcd_send_data(char data) {
    char data_u = (data & 0xF0);
    char data_l = ((data << 4) & 0xF0);
    uint8_t data_t[4];
    data_t[0] = data_u | 0x0D; // en=1, rs=1
    data_t[1] = data_u | 0x09; // en=0, rs=1
    data_t[2] = data_l | 0x0D; // en=1, rs=1
    data_t[3] = data_l | 0x09; // en=0, rs=1
    HAL_I2C_Master_Transmit(lcd_i2c, LCD_I2C_ADDR, data_t, 4, 50);
}

void lcd_init(I2C_HandleTypeDef *hi2c) {
    lcd_i2c = hi2c;
    HAL_Delay(50);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);
    HAL_Delay(10);

    lcd_send_cmd(0x28); // 4-bit, 2 line, 5x8 font
    lcd_send_cmd(0x08); // Display off
    lcd_send_cmd(0x01); // Clear display
    HAL_Delay(2);
    lcd_send_cmd(0x06); // Entry mode
    lcd_send_cmd(0x0C); // Display on, cursor off
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_print_str(char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

void lcd_print_num(int num) {
    char buf[16];
    sprintf(buf, "%d", num);
    lcd_print_str(buf);
}
