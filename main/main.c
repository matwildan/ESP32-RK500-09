#include <stdio.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "main.h"

const char *data_from_sensor;
const char *topic = "data";

void app_main() {
    gsm_init();

    mqtt_init();

    rs485_main();

    publish_data(data_from_sensor, "data");
}
