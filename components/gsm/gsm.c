#include <stdio.h>
#include "esp_event.h"
#include "gsm.h"

esp_mqtt_client_handle_t client;

static const char *MQTT_TAG = "MQTT_EXAMPLE";
static const char *BROKER_URL = "mqtt://174.138.24.9";
static const int BROKER_PORT = 1883;
static const int CLIENT_ID = 1;
static const char *MQTT_USERNAME = "abc";
static const char *MQTT_PASSWORD = "qwerty123";


// Function untuk inisialisasi GSM module UART interface
void gsm_init(){
    uart_config_t uart_config = {
        .baud_rate = UART_GSM_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, UART_TX_GSM_PIN, UART_RX_GSM_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
}

void mqtt_init(){
    // Open mqtt network
    char mqtt_open_cmd[256];
    sprintf(mqtt_open_cmd, "AT+QMTOPEN=0,\"%s\",%d\r\n", (char*)BROKER_URL, BROKER_PORT);
    uart_write_bytes(UART_NUM_1, mqtt_open_cmd, strlen(mqtt_open_cmd));
    vTaskDelay(2000/portTICK_PERIOD_MS);

    // Connect to mqtt network
    char mqtt_connect_cmd[256];
    sprintf(mqtt_connect_cmd, "AT+QMTCONN=0,%d,\"%s\",\"%s\"\r\n", CLIENT_ID, (char*)MQTT_USERNAME, (char*)MQTT_PASSWORD);
    uart_write_bytes(UART_NUM_1, mqtt_connect_cmd, strlen(mqtt_connect_cmd));
    vTaskDelay(2000/portTICK_PERIOD_MS);

    // Clear buffer
    memset(mqtt_open_cmd, 0, sizeof(mqtt_open_cmd));
    memset(mqtt_connect_cmd, 0, sizeof(mqtt_connect_cmd));
}

void publish_data(const char *data, const char *topic)
{
    // Publish data to MQTT
    char mqtt_publish_cmd[256];
    sprintf(mqtt_publish_cmd, "AT+QMTPUB=0,0,0,0,\"%s\",%d\r\n", topic, strlen(data));
    uart_write_bytes(UART_NUM_1, mqtt_publish_cmd, strlen(mqtt_publish_cmd));
    vTaskDelay(1000);

    uart_write_bytes(UART_NUM_1, data, strlen(data));
    vTaskDelay(2000);

    // Clear buffer
    memset(mqtt_publish_cmd, 0, sizeof(mqtt_publish_cmd));
}

