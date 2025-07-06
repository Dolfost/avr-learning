#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

void transmit_byte(uint8_t data) {
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = data;
}
uint8_t receive_byte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}
void print_string(const char str[]) {
  uint8_t i = 0;
  while (str[i]) {
    transmit_byte(str[i]);
    i++;
  }
}

#define LED_DDR DDRB
#define LED_PORT PORTB

int main(void) {
	// USART init
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  UCSR0A |= (1 << U2X0);
	// Enable USART transmitter/receiver
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
	
	LED_DDR = 0xff;
	char serial_char;

	print_string("hello this is me\n");
	while (1) {	
		serial_char = receive_byte();
		transmit_byte(serial_char);
		LED_PORT = serial_char;
	}

	return 0;
}
