/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com
 */

#ifndef __MUTERM_H__
#define __MUTERM_H__

unsigned int muterm_tx_ready(void);
void muterm_putc(int c);
unsigned int muterm_rx_ready(void);
unsigned int muterm_getc(void);
void muterm_flush_rx(void);
void muterm_disable(void);

#define MUTERM_8BIT		(1 << 1)
#define MUTERM_7BIT		(0 << 1)

#define MUTERM_115200_BAUD	(1 << 2)
#define MUTERM_57600_BAUD	(1 << 3)
#define MUTERM_38400_BAUD	(1 << 4)
#define MUTERM_19200_BAUD	(1 << 5)
#define MUTERM_14400_BAUD	(1 << 6)
#define MUTERM_9600_BAUD	(1 << 7)
#define MUTERM_4800_BAUD	(1 << 8)
#define MUTERM_2400_BAUD	(1 << 9)
#define MUTERM_1200_BAUD	(1 << 10)
#define MUTERM_600_BAUD		(1 << 11)

void muterm_enable(unsigned long flags);

#endif /* __MUTERM_H__ */
