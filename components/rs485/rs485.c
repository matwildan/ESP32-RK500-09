#include "rs485.h"

uint8_t tx_data[] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x70, 0x0D}; // Pesan yang akan dikirimkan ke sensor agar sensor memberi balasan data
//uint8_t tx_data[] = {0xB4, 0xC0, 0xA8, 0x01, 0x01, 0x00, 0x1A}; // Pesan yang akan dikirimkan ke sensor agar sensor memberi balasan data

void rs485_init() {
    gpio_set_direction(RS485_TXD_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(RS485_RXD_PIN, GPIO_MODE_INPUT);

    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        //.source_clk = UART_SCLK_DEFAULT
    };

    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, RS485_TXD_PIN, RS485_RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uart_driver_install(UART_NUM, UART_BUF_SIZE * 2, 0, 0, NULL, 0);

    //uart_enable_swap();
}

void rs485_send(uint8_t *data, size_t len) {
    gpio_set_level(RS485_TXD_PIN, 1);
    uart_write_bytes(UART_NUM, (const char*)data, len);
    //uart_write_bytes(UART_NUM, "\r\n", len);
    uart_wait_tx_done(UART_NUM, 100 / portTICK_PERIOD_MS);
    gpio_set_level(RS485_TXD_PIN, 0);
}

void rs485_recv(uint8_t *data, size_t len) {
    uart_read_bytes(UART_NUM, data, len, 100 / portTICK_PERIOD_MS);
}

char* rs485_main() {
    char* payload = (char*)malloc(256);

    rs485_init();

    while(1){
        rs485_send(tx_data, sizeof(tx_data));

        uint8_t rx_data[sizeof(tx_data)];
        rs485_recv(rx_data, sizeof(rx_data));

        printf("Received data:");
        for (int i = 0; i < sizeof(rx_data); i++) {
            printf(" 0x%02x", rx_data[i]);
        }
        printf("\n");

        /* Tambahkan di sini proses pengolahan data yang telah diterima */
        sprintf(payload, "%s", rx_data);
        return payload;

    }
}
