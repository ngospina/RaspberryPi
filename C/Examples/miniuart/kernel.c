/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com
 */

#include "miniuart.h"

static unsigned int get_nibble(unsigned int);

int kernel(void)
{
	unsigned int n;

	miniuart_enable(MINIUART_8BIT | MINIUART_115200_BAUD);
	while (1)
	{
		n = miniuart_getc();
		miniuart_putc(get_nibble((n >> 4) & 0xF));
		miniuart_putc(get_nibble(n & 0xF));
		miniuart_putc('\r');
		miniuart_putc('\n');
	}
	return 0;
}

static unsigned int get_nibble(unsigned int nibble)
{
	return nibble > 9 ? ((nibble - 10) + 'A') : (nibble + '0');
}
