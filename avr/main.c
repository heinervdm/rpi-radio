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
#define ENC0B_P    PD2
#define ENC1A_P    PD3
#define ENC1B_P    PD2

#define PHASE_0A     (ENC_PIN & 1<<ENC0A_P)
#define PHASE_0B     (ENC_PIN & 1<<ENC0B_P)
#define PHASE_1A     (ENC_PIN & 1<<ENC1A_P)
#define PHASE_1B     (ENC_PIN & 1<<ENC1B_P)

#define LIMIT0_PIN  PIND
#define LIMIT0_PORT PORTD
#define LIMIT0_DDR  DDRD
#define LIMIT0_P    PD1

#define LIMIT1_PIN  PIND
#define LIMIT1_PORT PORTD
#define LIMIT1_DDR  DDRD
#define LIMIT1_P    PD0

volatile int8_t enc_delta0, enc_delta1; // -128 ... 127
static int8_t last0, last1;

int main(void) {
	int16_t c;
	int32_t enc_pos0, enc_pos1;
	char tc;

	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	ENC_DDR  &= (0<<ENC0A_P) ^ (0<<ENC0B_P) ^ (0<<ENC1A_P) ^ (0<<ENC1B_P); // set ENC0 pin as input
	ENC_PORT |= (0<<ENC0A_P) ^ (0<<ENC0B_P) ^ (0<<ENC1A_P) ^ (0<<ENC1B_P); // enable internal pullups for ENC1 pin
	LIMIT0_DDR &= (0<<LIMIT0_P);  // set LIMIT0 pin as input
	LIMIT1_DDR &= (0<<LIMIT1_P);  // set LIMIT1 pin as input
	LIMIT0_PORT |= (1<<LIMIT0_P); // enable internal pullups for LIMIT0 pin
	LIMIT1_PORT |= (1<<LIMIT1_P); // enable internal pullups for LIMIT1 pin

	encode_init();
	sei();

	uart_puts("Encoder reader started.\n");

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
				case 'r':
				case 'R':
					break;
				default:
					uart_puts("Error: ");
					uart_putc(tc);
					uart_putc('\n');
					break;
			}
		}
		enc_pos0 += encode_read0();
		enc_pos1 += encode_read1();
	}
	return 0;
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
	TIMSK0 |= (1<<OCIE0A);                     // activate compare mode
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
}

int8_t encode_read0( void ) {        // read two step encoders
	int8_t val;

	cli();
	val = enc_delta0;
	enc_delta0 = val & 1;
	sei();
	return val >> 1;
}

int8_t encode_read2( void ) {        // read two step encoders
	int8_t val;

	cli();
	val = enc_delta1;
	enc_delta1 = val & 1;
	sei();
	return val >> 1;
}
