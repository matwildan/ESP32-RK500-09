#include <stdio.h>
#include "gsm.h"

// Function untuk inisialisasi GSM module UART interface
static void gsm_init(void)
{
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
}

void mqtt_init()
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtt://test.mosquitto.org", // or any other MQTT broker URI
        .event_handle = mqtt_event_handler,
        .disable_auto_reconnect = false,
        .keepalive = 120,
        .user_context = (void *)your_context
    };

    esp_mqtt_client_handle_t mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(mqtt_client);

}

void publish_data(const char *data, const char *topic)
{
    esp_mqtt_client_publish(mqtt_client, topic, data, strlen(data), 0, 0);
}
