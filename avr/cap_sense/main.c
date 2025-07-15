/*
   Capacitive touch sensor demo
*/

#include "pins.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

#include <avrtools/usart.h>

#define SENSE_TIME 100
#define THRESHOLD 830

volatile uint32_t chargeCycleCount;

void initPinChangeInterrupt(void) {
  PCICR |= (1 << PCIE1); /* enable Pin-change interrupts 1 (bank C) */
  PCMSK1 |= (1 << PC1);  /* enable specific interrupt for our pin PC1 */
}

ISR(PCINT1_vect) {
  chargeCycleCount++;

  CAP_SENSOR_DDR |= (1 << CAP_SENSOR); /* output mode */
  _delay_us(1);                        /* charging delay */

  CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR); /* set as input */
  PCIFR |= (1 << PCIF1); /* clear the pin-change interrupt */
}

int main(void) {
  usart_init();
  usart_print_string("==[ Cap Sensor ]==\r\n\r\n");

  LED_DDR = 0xff;
  MCUCR |= (1 << PUD); /* disable all pullups */
  CAP_SENSOR_PORT |= (1 << CAP_SENSOR);

  initPinChangeInterrupt();

  while (1) {
    chargeCycleCount = 0; /* reset counter */
    CAP_SENSOR_DDR |= (1 << CAP_SENSOR);
    sei();
    _delay_ms(SENSE_TIME);
    cli();
    if (chargeCycleCount < THRESHOLD)
      LED_PORT = 0xff;
    else
      LED_PORT = 0;
    usart_print_long(chargeCycleCount);
    usart_print_string("\r\n");
  }

  return 0;
}
