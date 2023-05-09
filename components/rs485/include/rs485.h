#ifndef RS485_H
#define RS485_H

#include <stdio.h>
#include "driver/uart.h"
#include "driver/gpio.h"

#define RS485_TXD_PIN (GPIO_NUM_17)
#define RS485_RXD_PIN (GPIO_NUM_16)

#define UART_NUM UART_NUM_2
#define UART_BUF_SIZE (1024)

/* Inisialisasi/config UART RS485 */
void rs485_init();

/* Pengiriman data UART RS485 */
void rs485_send(uint8_t *data, size_t len);

/* Penerimaan data UART RS485 */
void rs485_recv(uint8_t *data, size_t len);

/* Function main RS485 */
char* rs485_main();

#endif
