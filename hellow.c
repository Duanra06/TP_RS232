#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define USART_BAUDRATE (9600)

void uart_transmit(unsigned char data)
{
	while (!(UCSR1A&(1<<UDRE1)));
	UDR1 = data;
}

unsigned char uart_receive(void)
{
	while (!(UCSR1A&(1<<RXC1)));
	return UDR1;
}

int main(void)
{
	unsigned short baud;
	//char c[2] = {72, 101, };
	char c[11] = "Hello World";
	int i;

	DDRB |= 1<<PORTB5;
	DDRE |= 1<<PORTE6;
	PORTB |= 1<<PORTB5;
	PORTE &= -(1<<PORTE6);

	UCSR1A = 0;
	UCSR1B = 0;
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
        UCSR1C = _BV(UCSZ11) | _BV(UCSZ10);

	baud = ((((F_CPU/(USART_BAUDRATE*16UL)))-1));
	UBRR1H = (unsigned char)(baud>>8);
	UBRR1L = (unsigned char)baud;
	
	while (1)
	{
		PORTB ^= 1<<PORTB5;
		PORTE ^= 1<<PORTE6;
		_delay_ms(10);
		
		//if (flag == 0)
		//{	
			for (i = 0; i<11; i++)
			{
				uart_transmit(c[i]);
			}
			//flag = 1;
		//}
	
		//c++;
		//if (c==127) c=32;
	}	
	return 0;
}
