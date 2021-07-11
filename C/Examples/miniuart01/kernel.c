/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com
 */

#include "io.h"
#include "miniuart.h"

int kernel(void)
{
    unsigned int n;

    miniuart_enable(MINIUART_INT_DISABLE | MINIUART_8BIT | MINIUART_115200_BAUD);
    n = 0;
    while (1)
    {
        miniuart_putc('0' + n);
	n = (n + 1) % 8;
    }
    return 0;
}
