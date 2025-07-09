#include <avrtools/usart.h>

#include <avr/io.h>
#include <stdlib.h>

void usart_transmit_byte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}

uint8_t usart_receive_byte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

void usart_print_string(const char str[]) {
	for (uint16_t i = 0; str[i]; i++)
    usart_transmit_byte(str[i]);
}

void usart_print_int(int num) {
	char str[7];
	itoa(num, str, 10);
	usart_print_string(str);
}

void usart_print_long(long num) {
	char str[12];
	ltoa(num, str, 10);
	usart_print_string(str);
}
