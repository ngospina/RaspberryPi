#include "io.h"
#include "miniuart.h"

#define AUX_ENB_REG_OFFS		0x04
#define		ENB_MINIUART_ENA_MASK	(1 << 0)
#define		ENB_MINIUART_DIS_MASK	(0 << 0)

#define AUX_MU_IO_REG_OFFS		0x40

#define AUX_MU_IER_REG_OFFS     	0x44
#define		IER_RX_IENA_MASK	(1 << 0)
#define		IER_RX_IDIS_MASK	(0 << 0)
#define		IER_TX_IENA_MASK	(1 << 1)
#define		IER_TX_IDIS_MASK	(0 << 1)
#define		IER_BAUD_MASK		0x7

#define AUX_MU_IIR_REG_OFFS		0x48
#define		IIR_INT_PEND_MASK	(1 << 0)
#define		IIR_INT_ID_MASK		(3 << 1)
#define		IIR_CLR_RX_FIFO_MASK	(1 << 1)
#define		IIR_CLR_TX_FIFO_MASK	(1 << 2)

#define AUX_MU_LCR_REG_OFFS		0x4C
#define		LCR_7BIT_MODE_MASK	(0 << 0)
#define		LCR_8BIT_MODE_MASK	(3 << 0)
#define		LCR_TX_LO_MASK		(1 << 6)
#define		LCR_DLAB_ENA_MASK	(1 << 7)

#define AUX_MU_MCR_REG_OFFS		0x50
#define		MCR_RTS_LO_MASK		(1 << 1)
#define		MCR_RTS_HI_MASK		(0 << 1)

#define AUX_MU_LSR_REG_OFFS		0x54
#define		LSR_RX_DATA_READY_MASK	(1 << 0)
#define		LSR_RX_OVERRUN_MASK	(1 << 1)
#define		LSR_TX_EMPTY_MASK	(1 << 5)
#define		LSR_TX_IDLE_MASK	(1 << 6)

#define AUX_MU_MSR_REG_OFFS		0x58
#define		MSR_RTS_LO_MASK		(1 << 4)

#define AUX_MU_SCRATCH_REG_OFFS		0x5C
#define		SCRATCH_DATA_MASK	0x7

#define AUX_MU_CNTL_REG_OFFS		0x60
#define		CNTL_RX_ENA_MASK	(1 << 0)
#define		CNTL_TX_ENA_MASK	(1 << 1)
#define		CNTL_RTS_AUTOFLOW_MASK	(1 << 2)
#define		CNTL_TX_CTS_AFLOW_MASK	(1 << 3)
#define		CNTL_RTS_AF_LVL3_MASK	(0 << 4)
#define		CNTL_RTS_AF_LVL2_MASK	(1 << 4)
#define		CNTL_RTS_AF_LVL1_MASK	(2 << 4)
#define		CNTL_RTS_AF_LVL4_MASK	(3 << 4)
#define		CNTL_RTS_AF_LVL_LO_MASK	(1 << 6)
#define		CNTL_CTS_AF_LVL_LO_MASK	(1 << 7)

#define AUX_MU_STAT_REG_OFFS		0x64
#define		STAT_RX_FIFO_SYMBL_MASK	(1 << 0)
#define		STAT_TX_FIFO_SPACE_MASK	(1 << 1)
#define		STAT_RX_IDLE_MASK	(1 << 2)
#define		STAT_TX_IDLE_MASK	(1 << 3)
#define		STAT_RX_OVERRUN_MASK	(1 << 4)
#define		STAT_TX_FIFO_FULL_MASK	(1 << 5)
#define		STAT_RTS_STATUS_MASK	(1 << 6)
#define		STAT_CTS_STATUS_MASK	(1 << 7)
#define		STAT_TX_FIFO_EMPTY_MASK	(1 << 8)
#define		STAT_TX_DONE_MASK	(1 << 9)
#define		STAT_RX_FIFO_LEVEL_MASK	(15 << 16)
#define		STAT_TX_FIFO_LEVEL_MASK	(15 << 24)

#define AUX_MU_BAUD_REG_OFFS		0x68
#define		BAUD_RATE		(15 << 0)

#define AUX_ENB_REG		(AUX_PERIPH_BASE + AUX_ENB_REG_OFFS)
#define AUX_MU_IO_REG		(AUX_PERIPH_BASE + AUX_MU_IO_REG_OFFS)
#define AUX_MU_IER_REG		(AUX_PERIPH_BASE + AUX_MU_IER_REG_OFFS)
#define AUX_MU_IIR_REG		(AUX_PERIPH_BASE + AUX_MU_IIR_REG_OFFS)
#define AUX_MU_LCR_REG		(AUX_PERIPH_BASE + AUX_MU_LCR_REG_OFFS)
#define AUX_MU_MCR_REG		(AUX_PERIPH_BASE + AUX_MU_MCR_REG_OFFS)
#define AUX_MU_LSR_REG		(AUX_PERIPH_BASE + AUX_MU_LSR_REG_OFFS)
#define AUX_MU_MSR_REG		(AUX_PERIPH_BASE + AUX_MU_MSR_REG_OFFS)
#define AUX_MU_SCRATCH_REG	(AUX_PERIPH_BASE + AUX_MU_SCRATCH_REG_OFFS)
#define AUX_MU_CNTL_REG		(AUX_PERIPH_BASE + AUX_MU_CNTL_REG_OFFS)
#define AUX_MU_STAT_REG		(AUX_PERIPH_BASE + AUX_MU_STAT_REG_OFFS)
#define AUX_MU_BAUD_REG		(AUX_PERIPH_BASE + AUX_MU_BAUD_REG_OFFS)

#define BAUDRATE_REG(baudrate)	(((SYSTEM_CLOCK_FREQUENCY / (baudrate)) / 8) - 1)

#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define GPPUD       0x20200094
#define GPPUDCLK0   0x20200098

//GPIO14  TXD0 and TXD1
////GPIO15  RXD0 and RXD1
////alt function 5 for uart1
////alt function 0 for uart0

static unsigned int miniuart_baudrate_reg(unsigned int);
static void miniuart_wait(unsigned int);

void miniuart_putc(int c)
{
	while (!(readl(AUX_MU_LSR_REG) & LSR_TX_IDLE_MASK))
		continue;
	writel(AUX_MU_IO_REG, c);

	if (c == '\n')
		miniuart_putc('\r');
}

unsigned int miniuart_getc(void)
{
	return 0;
/*
        while (!(readl(AUX_MU_LSR_REG) & LSR_RX_DATA_READY_MASK))
		continue;
	return readl(AUX_MU_IO_REG) & 0xFF;
*/
}

void miniuart_flush_rx(void)
{
/*
	while (readl(AUX_MU_LSR_REG) & LSR_RX_DATA_READY_MASK)
		miniuart_getc();
*/
}

void miniuart_disable(void)
{
	writel(AUX_ENB_REG, readl(AUX_ENB_REG) & (~ENB_MINIUART_ENA_MASK));
}

void miniuart_enable(unsigned long flags)
{
	unsigned int ra;

	ra=readl(GPFSEL1);
	ra&=~(7<<12); //gpio14
	ra|=2<<12;    //alt5
	writel(GPFSEL1,ra);

	writel(GPPUD,0);
        miniuart_wait(150);
	writel(GPPUDCLK0,(1<<14));
        miniuart_wait(150);
	writel(GPPUDCLK0,0);

	writel(AUX_ENB_REG, readl(AUX_ENB_REG) | ENB_MINIUART_ENA_MASK);
	if (flags & MINIUART_INT_ENABLE)
		writel(AUX_MU_IER_REG, IER_RX_IENA_MASK | IER_TX_IENA_MASK);
	else
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
