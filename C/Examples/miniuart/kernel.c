/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com
 */

#include "muterm.h"

static unsigned int get_nibble(unsigned int);

int kernel(void)
{
	unsigned int n;

	muterm_enable(MUTERM_8BIT | MUTERM_115200_BAUD);
	while (1)
	{
		n = muterm_getc();
		muterm_putc(get_nibble((n >> 4) & 0xF));
		muterm_putc(get_nibble(n & 0xF));
		muterm_putc('\r');
		muterm_putc('\n');
	}
	return 0;
}

static unsigned int get_nibble(unsigned int nibble)
{
	return nibble > 9 ? ((nibble - 10) + 'A') : (nibble + '0');
}
