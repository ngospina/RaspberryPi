/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com
 */

#include "io.h"
#include "miniuart.h"

static unsigned int get_nibble(unsigned int);

void hexstrings(unsigned int d)
{
	unsigned int rb;
	unsigned int rc;

	rb = 32;
	while (1)
	{
		rb -= 4;
		rc = (d >> rb) & 0xF;
		if (rc > 9) rc += 'A'; else rc += '0';
		miniuart_putc(rc);
		if (rb == 0) break;
	}
	miniuart_putc(' ');
}

void hexstring (unsigned int d)
{
	hexstrings(d);
	miniuart_putc('\r');
	miniuart_putc('\n');
}

int kernel(void)
{
	unsigned int n;

	miniuart_enable(MINIUART_8BIT | MINIUART_115200_BAUD);
	hexstring(0x12345678);
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
