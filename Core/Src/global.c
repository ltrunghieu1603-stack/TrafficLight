#include "global.h"
#include <stdio.h>

int status = INIT;
int time_red = 5000;
int time_amber = 2000;
int time_green = 3000;
int temp_time = 0;

void lcd_display_system(void) {
    char line0[17];
    char line1[17];

    if (status >= AUTO_RED1_GREEN2 && status <= AUTO_AMBER1_RED2) {
        sprintf(line0, "MODE: AUTO      ");
        sprintf(line1, "T:%2dC   H:%2d%%   ", (int)dht20_temperature, (int)dht20_humidity);
    } else if (status >= MAN_INIT && status <= MAN_GREEN1_RED2) {
        sprintf(line0, "MODE: MANUAL    ");
        sprintf(line1, "T:%2dC   H:%2d%%   ", (int)dht20_temperature, (int)dht20_humidity);
    } else if (status == TUN_RED) {
        sprintf(line0, "MODE: TUNING RED");
        sprintf(line1, "TIME: %2d s      ", temp_time / 1000);
    } else if (status == TUN_AMBER) {
        sprintf(line0, "MODE: TUN AMBER ");
        sprintf(line1, "TIME: %2d s      ", temp_time / 1000);
    } else if (status == TUN_GREEN) {
        sprintf(line0, "MODE: TUN GREEN ");
        sprintf(line1, "TIME: %2d s      ", temp_time / 1000);
    } else {
        sprintf(line0, "SYSTEM STARTING ");
        sprintf(line1, "                ");
    }

    lcd_set_cursor(0, 0);
    lcd_print_str(line0);
    lcd_set_cursor(1, 0);
    lcd_print_str(line1);
}
