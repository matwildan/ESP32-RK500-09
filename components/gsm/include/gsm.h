#ifndef GSM_H
#define GSM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "string.h"

#define BUF_SIZE 1024

#define UART_TX_PIN 17 // change to your GSM module's TX pin
#define UART_RX_PIN 16 // change to your GSM module's RX pin
#define UART_BAUD_RATE 9600

static void gsm_init(void);

void mqtt_init();

void publish_data(const char *data, const char *topic);

#endif
