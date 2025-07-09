#ifndef _AVRTOOLS_USART_H_
#define _AVRTOOLS_USART_H_

#include <avr/io.h>
#include <util/setbaud.h>
#include <stdint.h>

/**
 * @brief Initialize USART in asynchronyous mode with 8 data bits and 1 stop
 * bit
 */
static inline void usart_init();
/**
 * @brief Transmit one byte over USART 
 *
 * @param data input byte
 */
void usart_transmit_byte(uint8_t data);
/**
 * @brief Recieve one byte over USART
 *
 * @return recieved byte 
 */
uint8_t usart_receive_byte();
/**
 * @brief Print string over USART
 *
 * @param str input string
 */
void usart_print_string(const char str[]);
/**
 * @brief Convert `long` to `char[]` and send it over USART
 *
 * @param num input `long` integer
 */
void usart_print_long(long num);
/**
 * @brief Convert `int` to `char[]` and send it over USART
 *
 * @param num input integer
 */
void usart_print_int(int num);


static inline void usart_init() { 
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0A |= (1 << U2X0);
	// Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

#endif // _AVRTOOLS_USART_H_
