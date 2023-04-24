#ifndef GSM_H
#define GSM_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "string.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define BUF_SIZE 1024

#define UART_TX_PIN 9 // change to your GSM module's TX pin
#define UART_RX_PIN 10 // change to your GSM module's RX pin
#define UART_BAUD_RATE 9600

void gsm_init();

void log_error_if_nonzero(const char *message, int error_code);

void mqtt_init();

void publish_data(const char *data, const char *topic);

#endif
