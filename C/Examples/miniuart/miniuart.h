/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com
 */
#ifndef __MINIUART_H__
#define __MINIUART_H__

unsigned int miniuart_tx_ready(void);
void miniuart_putc(int c);
unsigned int miniuart_rx_ready(void);
unsigned int miniuart_getc(void);
void miniuart_flush_rx(void);
void miniuart_disable(void);

#define MINIUART_8BIT		(1 << 1)
#define MINIUART_7BIT		(0 << 1)

#define MINIUART_115200_BAUD	(1 << 2)
#define MINIUART_57600_BAUD	(1 << 3)
#define MINIUART_38400_BAUD	(1 << 4)
#define MINIUART_19200_BAUD	(1 << 5)
#define MINIUART_14400_BAUD	(1 << 6)
#define MINIUART_9600_BAUD	(1 << 7)
#define MINIUART_4800_BAUD	(1 << 8)
#define MINIUART_2400_BAUD	(1 << 9)
#define MINIUART_1200_BAUD	(1 << 10)
#define MINIUART_600_BAUD	(1 << 11)

void miniuart_enable(unsigned long flags);

#endif /* __MINIUART_H__ */
