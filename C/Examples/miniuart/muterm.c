/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com.
 */

#include "gpio.h"
#include "miniuart.h"
#include "muterm.h"

#define BAUDRATE(baudrate)	(((SYSTEM_CLOCK_FREQUENCY / (baudrate)) / 8) - 1)

#define MUTERM_BYTE	0xFF

static unsigned int baudrate_reg(unsigned int);
static void wait(unsigned int);

unsigned int muterm_tx_ready(void)
{
        return readl(MU_LSR) & LSR_TX_IDLE;
}

void muterm_putc(int c)
{
	while (!(readl(MU_LSR) & LSR_TX_IDLE))
		continue;
	if (c == '\n')
		writel(MU_IO, '\r');
	writel(MU_IO, c);
}

unsigned int muterm_rx_ready(void)
{
        return readl(MU_LSR) & LSR_RX_DATA_READY;
}

unsigned int muterm_getc(void)
{
        while (!(readl(MU_LSR) & LSR_RX_DATA_READY))
		continue;
	return readl(MU_IO) & MUTERM_BYTE;
}

void muterm_flush_rx(void)
{
	while (readl(MU_LSR) & LSR_RX_DATA_READY)
		readl(MU_IO);
}

void muterm_disable(void)
{
	writel(AUX_ENB, readl(AUX_ENB) & (~ENB_MU_ENA));
}

void muterm_enable(unsigned long flags)
{
	unsigned int ra;

	ra=readl(GPFSEL1);
	ra &= ~(7 << 12); // clean gpio14
	ra |= 2 << 12;    // set alt5 for gpio14
	ra &= ~(7 << 15); // clean gpio15
	ra |= 2 << 15;    // set alt5 for gpio15
	writel(GPFSEL1,ra);

	writel(GPPUD, 0);
        wait(150);
	writel(GPPUDCLK0, (1 << 14) | (1 << 15));
        wait(150);
	writel(GPPUDCLK0, 0);

	writel(AUX_ENB, readl(AUX_ENB) | ENB_MU_ENA);
	writel(MU_CNTL, CNTL_RX_DIS | CNTL_TX_DIS | CNTL_RTS_AFLOW_DIS);
	writel(MU_IER, IER_RX_IDIS | IER_TX_IDIS);
	writel(MU_IIR, IIR_CLR_RX_FIFO | IIR_CLR_TX_FIFO);
	if (flags & MUTERM_8BIT)
		writel(MU_LCR, LCR_8BIT_MODE);
	else
		writel(MU_LCR, LCR_7BIT_MODE);
	writel(MU_MCR, MCR_RTS_HI);
	writel(MU_BAUD, baudrate_reg(flags));
	writel(MU_CNTL, CNTL_RX_ENA | CNTL_TX_ENA);
}

static unsigned int baudrate_reg(unsigned int flags)
{
	if (flags & MUTERM_115200_BAUD)
		return BAUDRATE(115200);
	else if (flags & MUTERM_57600_BAUD)
		return BAUDRATE(57600);
	else if (flags & MUTERM_38400_BAUD)
		return BAUDRATE(38400);
	else if (flags & MUTERM_19200_BAUD)
		return BAUDRATE(19200);
	else if (flags & MUTERM_14400_BAUD)
		return BAUDRATE(14400);
	else if (flags & MUTERM_9600_BAUD)
		return BAUDRATE(9600);
	else if (flags & MUTERM_4800_BAUD)
		return BAUDRATE(4800);
	else if (flags & MUTERM_2400_BAUD)
		return BAUDRATE(2400);
	else if (flags & MUTERM_1200_BAUD)
		return BAUDRATE(1200);
	else if (flags & MUTERM_600_BAUD)
		return BAUDRATE(600);
	else
		return BAUDRATE(115200);
}

static void wait(unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		continue;
}
