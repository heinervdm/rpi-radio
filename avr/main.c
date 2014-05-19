/*
 * Debounce routine by Peter Dannegger: https://www.mikrocontroller.net/articles/Entprellung#Timer-Verfahren_.28nach_Peter_Dannegger.29
 * 
 * Rotary encoder routine by Peter Dannegger: https://www.mikrocontroller.net/articles/Drehgeber#Solide_L.C3.B6sung:_Beispielcode_in_C
 * 
 * UART lib by Peter Fleury: http://homepage.hispeed.ch/peterfleury/avr-software.html#libs
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>

#include "lib/uartlibrary/uart.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define UART_BAUD_RATE 9600

#define ENC_PIN    PIND
#define ENC_PORT   PORTD
#define ENC_DDR    DDRD
#define ENC0A_P    PD3
#define ENC0B_P    PD4
#define ENC1A_P    PD5
#define ENC1B_P    PD6

#define PHASE_0A     (ENC_PIN & 1<<ENC0A_P)
#define PHASE_0B     (ENC_PIN & 1<<ENC0B_P)
#define PHASE_1A     (ENC_PIN & 1<<ENC1A_P)
#define PHASE_1B     (ENC_PIN & 1<<ENC1B_P)

volatile int8_t enc_delta0, enc_delta1; // -128 ... 127
static int8_t last0, last1;

#define KEY_DDR         DDRB
#define KEY_PORT        PORTB
#define KEY_PIN         PINB
#define KEY0            0
#define KEY1            1
#define KEY2            2
#define ALL_KEYS        (1<<KEY0 | 1<<KEY1 | 1<<KEY2)
 
#define REPEAT_MASK     (1<<KEY1 | 1<<KEY2)       // repeat: key1, key2
#define REPEAT_START    250                       // after 250ms
#define REPEAT_NEXT     150                       // every 150ms
 
volatile uint8_t key_state;                                // debounced and inverted key state: bit = 1: key pressed
volatile uint8_t key_press;                                // key press detect
volatile uint8_t key_rpt;                                  // key long press and repeat

///////////////////////////////////////////////////////////////////
//
// check if a key has been pressed. Each pressed key is reported
// only once
//
uint8_t get_key_press( uint8_t key_mask ) {
	cli();                                          // read and clear atomic !
	key_mask &= key_press;                          // read key(s)
	key_press ^= key_mask;                          // clear key(s)
	sei();
	return key_mask;
}
 
///////////////////////////////////////////////////////////////////
//
// check if a key has been pressed long enough such that the
// key repeat functionality kicks in. After a small setup delay
// the key is reported being pressed in subsequent calls
// to this function. This simulates the user repeatedly
// pressing and releasing the key.
//
uint8_t get_key_rpt( uint8_t key_mask ) {
	cli();                                          // read and clear atomic !
	key_mask &= key_rpt;                            // read key(s)
	key_rpt ^= key_mask;                            // clear key(s)
	sei();
	return key_mask;
}
 
///////////////////////////////////////////////////////////////////
//
// check if a key is pressed right now
//
uint8_t get_key_state( uint8_t key_mask ) {
  key_mask &= key_state;
  return key_mask;
}
 
///////////////////////////////////////////////////////////////////
//
uint8_t get_key_short( uint8_t key_mask ) {
  cli();                                          // read key state and key press atomic !
  return get_key_press( ~key_state & key_mask );
}
 
///////////////////////////////////////////////////////////////////
//
uint8_t get_key_long( uint8_t key_mask ) {
  return get_key_press( get_key_rpt( key_mask ));
}


void encode_init( void ) {
	int8_t new;

	new = 0;
	if( PHASE_0A )
		new = 3;
	if( PHASE_0B )
		new ^= 1;
	last0 = new;

	new = 0;
	if( PHASE_1A )
		new = 3;
	if( PHASE_1B )
		new ^= 1;                              // convert gray to binary
	last1 = new;                               // power on state

	enc_delta0 = enc_delta1 = 0;
	TCCR0A = (1<<WGM01);                       // CTC
	TCCR0B = (1<<CS01)^(0<<CS00);              // XTAL / 8
	OCR0A = (uint8_t)(F_CPU / 128 / 1000 - 1); // set compare register
	TIMSK |= (1<<OCIE0A);                     // activate compare mode
}

int8_t encode_read0( void ) {        // read two step encoders
	int8_t val;

	cli();
	val = enc_delta0;
	enc_delta0 = val & 1;
	sei();
	return val >> 1;
}

int8_t encode_read1( void ) {        // read two step encoders
	int8_t val;

	cli();
	val = enc_delta1;
	enc_delta1 = val & 1;
	sei();
	return val >> 1;
}

int main(void) {
	int16_t c;
	int32_t enc_pos0, enc_pos1, last_enc_pos0, last_enc_pos1;
	char tc;
	char buf[12];

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	ENC_DDR  &= (0<<ENC0A_P) ^ (0<<ENC0B_P) ^ (0<<ENC1A_P) ^ (0<<ENC1B_P); // set ENC pin as input
	ENC_PORT |= (1<<ENC0A_P) ^ (1<<ENC0B_P) ^ (1<<ENC1A_P) ^ (1<<ENC1B_P); // enable internal pullups for ENC pin
	KEY_DDR &= ~ALL_KEYS;                // configure key port for input
	KEY_PORT |= ALL_KEYS;                // and turn on pull up resistors

	encode_init();
	sei();

	uart_puts("Info: Encoder reader started.\n");

	last_enc_pos0 = enc_pos0 = 0;
	last_enc_pos1 = enc_pos1 = 0;

	while (1) {
		c = uart_getc();
		if ( c & UART_NO_DATA ) {
		} else {
			if ( c & UART_FRAME_ERROR ) {
				uart_puts("Error: UART Framing\n");
			}
			if ( c & UART_OVERRUN_ERROR ) {
				uart_puts("Error: UART Overrun\n");
			}
			if ( c & UART_BUFFER_OVERFLOW ) {
				uart_puts("Error: Buffer Overflow\n");
			}
			tc = c & 0x00FF;
			switch (tc) {
				case '\r':
				case '\n':
				case '\0':
					break;
				case 's':
				case 'S':
					break;
				default:
					uart_puts("Error: Unknown command: ");
					uart_putc(tc);
					uart_putc('\n');
					break;
			}
		}
		enc_pos0 += encode_read0();
		if ( enc_pos0 != last_enc_pos0 ) {
			uart_puts("Encoder L: ");
			itoa( enc_pos0, buf, 10 );
			uart_puts(buf);
			uart_putc('\n');
			last_enc_pos0 = enc_pos0;
		}
		enc_pos1 += encode_read1();
		if ( enc_pos1 != last_enc_pos1 ) {
			uart_puts("Encoder R: ");
			itoa( enc_pos1, buf, 10 );
			uart_puts(buf);
			uart_putc('\n');
			last_enc_pos1 = enc_pos1;
		}
		if( get_key_press( 1<<KEY0 ) || get_key_rpt( 1<<KEY0 )){
			uart_puts("Button Pressed: L\n");
		}
		if( get_key_press( 1<<KEY1 ) || get_key_rpt( 1<<KEY1 )){
			uart_puts("Button Pressed: M\n");
		}
		if( get_key_press( 1<<KEY2 ) || get_key_rpt( 1<<KEY2 )){
			uart_puts("Button Pressed: R\n");
		}
	}
	return 0;
}


ISR( TIMER0_COMPA_vect ) {              // poll encoder
	int8_t new, diff;

	new = 0;
	if( PHASE_0A )
		new = 3;
	if( PHASE_0B )
		new ^= 1;                       // convert gray to binary
	diff = last0 - new;                 // difference last - new
	if( diff & 1 ){                     // bit 0 = value (1)
		last0 = new;                    // store new as next last
		enc_delta0 += (diff & 2) - 1;   // bit 1 = direction (+/-)
	}

	new = 0;
	if( PHASE_1A )
		new = 3;
	if( PHASE_1B )
		new ^= 1;                       // convert gray to binary
	diff = last1 - new;                 // difference last - new
	if( diff & 1 ){                     // bit 0 = value (1)
		last1 = new;                    // store new as next last
		enc_delta1 += (diff & 2) - 1;   // bit 1 = direction (+/-)
	}

	static uint8_t ct0, ct1, rpt;
	uint8_t i;
	i = key_state ^ ~KEY_PIN;                       // key changed ?
	ct0 = ~( ct0 & i );                             // reset or count ct0
	ct1 = ct0 ^ (ct1 & i);                          // reset or count ct1
	i &= ct0 & ct1;                                 // count until roll over ?
	key_state ^= i;                                 // then toggle debounced state
	key_press |= key_state & i;                     // 0->1: key press detect
	
	if( (key_state & REPEAT_MASK) == 0 )            // check repeat function
		rpt = REPEAT_START;                          // start delay
	if( --rpt == 0 ){
		rpt = REPEAT_NEXT;                            // repeat delay
		key_rpt |= key_state & REPEAT_MASK;
	}
}

