/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com.
 */

#include "gpio.h"
#include "auxio.h"
#include "miniuart.h"

#define BAUDRATE_REG(baudrate)	(((SYSTEM_CLOCK_FREQUENCY / (baudrate)) / 8) - 1)

#define MINIUART_BYTE_MASK	0xFF

static unsigned int miniuart_baudrate_reg(unsigned int);
static void miniuart_wait(unsigned int);

unsigned int miniuart_tx_ready(void)
{
        return readl(AUX_MU_LSR_REG) & LSR_TX_IDLE_MASK;
}

void miniuart_putc(int c)
{
	while (!(readl(AUX_MU_LSR_REG) & LSR_TX_IDLE_MASK))
		continue;
	if (c == '\n')
		writel(AUX_MU_IO_REG, '\r');
	writel(AUX_MU_IO_REG, c);
}

unsigned int miniuart_rx_ready(void)
{
        return readl(AUX_MU_LSR_REG) & LSR_RX_DATA_READY_MASK;
}

unsigned int miniuart_getc(void)
{
        while (!(readl(AUX_MU_LSR_REG) & LSR_RX_DATA_READY_MASK))
		continue;
	return readl(AUX_MU_IO_REG) & MINIUART_BYTE_MASK;
}

void miniuart_flush_rx(void)
{
	while (readl(AUX_MU_LSR_REG) & LSR_RX_DATA_READY_MASK)
		readl(AUX_MU_IO_REG);
}

void miniuart_disable(void)
{
	writel(AUX_ENB_REG, readl(AUX_ENB_REG) & (~ENB_MINIUART_ENA_MASK));
}

void miniuart_enable(unsigned long flags)
{
	unsigned int ra;

	ra=readl(GPFSEL1);
	ra &= ~(7 << 12); // clean gpio14
	ra |= 2 << 12;    // set alt5 for gpio14
	ra &= ~(7 << 15); // clean gpio15
	ra |= 2 << 15;    // set alt5 for gpio15
	writel(GPFSEL1,ra);

	writel(GPPUD,0);
        miniuart_wait(150);
	writel(GPPUDCLK0,(1 << 14) | (1 << 15));
        miniuart_wait(150);
	writel(GPPUDCLK0,0);

	writel(AUX_ENB_REG, readl(AUX_ENB_REG) | ENB_MINIUART_ENA_MASK);
	writel(AUX_MU_CNTL_REG, CNTL_RX_DIS_MASK | CNTL_TX_DIS_MASK | CNTL_RTS_AFLOW_DIS_MASK);
	writel(AUX_MU_IER_REG, IER_RX_IDIS_MASK | IER_TX_IDIS_MASK);
	writel(AUX_MU_IIR_REG, IIR_CLR_RX_FIFO_MASK | IIR_CLR_TX_FIFO_MASK);
	if (flags & MINIUART_8BIT)
		writel(AUX_MU_LCR_REG, LCR_8BIT_MODE_MASK);
	else
		writel(AUX_MU_LCR_REG, LCR_7BIT_MODE_MASK);
	writel(AUX_MU_MCR_REG, MCR_RTS_HI_MASK);
	writel(AUX_MU_BAUD_REG, miniuart_baudrate_reg(flags));
	writel(AUX_MU_CNTL_REG, CNTL_RX_ENA_MASK | CNTL_TX_ENA_MASK);
}

static unsigned int miniuart_baudrate_reg(unsigned int flags)
{
	if (flags & MINIUART_115200_BAUD)
		return BAUDRATE_REG(115200);
	else if (flags & MINIUART_57600_BAUD)
		return BAUDRATE_REG(57600);
	else if (flags & MINIUART_38400_BAUD)
		return BAUDRATE_REG(38400);
	else if (flags & MINIUART_19200_BAUD)
		return BAUDRATE_REG(19200);
	else if (flags & MINIUART_14400_BAUD)
		return BAUDRATE_REG(14400);
	else if (flags & MINIUART_9600_BAUD)
		return BAUDRATE_REG(9600);
	else if (flags & MINIUART_4800_BAUD)
		return BAUDRATE_REG(4800);
	else if (flags & MINIUART_2400_BAUD)
		return BAUDRATE_REG(2400);
	else if (flags & MINIUART_1200_BAUD)
		return BAUDRATE_REG(1200);
	else if (flags & MINIUART_600_BAUD)
		return BAUDRATE_REG(600);
	else
		return BAUDRATE_REG(115200);
}

static void miniuart_wait(unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		continue;
}
