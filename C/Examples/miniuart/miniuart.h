/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com.
 */

#ifndef __MINIUART_H__
#define __MINIUART_H__

#include "auxiliary.h"

#define MU_IO		(AUX_BASE + 0x40)

#define MU_IER		(AUX_BASE + 0x44)
#define		IER_RX_IENA		(1 << 0)
#define		IER_RX_IDIS		(0 << 0)
#define		IER_TX_IENA		(1 << 1)
#define		IER_TX_IDIS		(0 << 1)
#define		IER_BAUD		0x7

#define MU_IIR		(AUX_BASE + 0x48)
#define		IIR_INT_PEND		(1 << 0)
#define		IIR_INT_ID		(3 << 1)
#define		IIR_CLR_RX_FIFO		(1 << 1)
#define		IIR_CLR_TX_FIFO		(1 << 2)

#define MU_LCR		(AUX_BASE + 0x4C)
#define		LCR_7BIT_MODE		(0 << 0)
#define		LCR_8BIT_MODE		(3 << 0)
#define		LCR_TX_LO		(1 << 6)
#define		LCR_DLAB_ENA		(1 << 7)

#define MU_MCR		(AUX_BASE + 0x50)
#define		MCR_RTS_LO		(1 << 1)
#define		MCR_RTS_HI		(0 << 1)

#define MU_LSR		(AUX_BASE + 0x54)
#define		LSR_RX_DATA_READY	(1 << 0)
#define		LSR_RX_OVERRUN	(1 << 1)
#define		LSR_TX_EMPTY	(1 << 5)
#define		LSR_TX_IDLE	(1 << 6)

#define MU_MSR		(AUX_BASE + 0x58)
#define		MSR_RTS_LO		(1 << 4)

#define MU_SCRATCH	(AUX_BASE + 0x5C)
#define		SCRATCH_DATA		0x7

#define MU_CNTL		(AUX_BASE + 0x60)
#define		CNTL_RX_ENA		(1 << 0)
#define		CNTL_RX_DIS		(0 << 0)
#define		CNTL_TX_ENA		(1 << 1)
#define		CNTL_TX_DIS		(0 << 1)
#define		CNTL_RTS_AFLOW_ENA	(1 << 2)
#define		CNTL_RTS_AFLOW_DIS	(0 << 2)
#define		CNTL_TX_CTS_AFLOW	(1 << 3)
#define		CNTL_RTS_AF_LVL3	(0 << 4)
#define		CNTL_RTS_AF_LVL2	(1 << 4)
#define		CNTL_RTS_AF_LVL1	(2 << 4)
#define		CNTL_RTS_AF_LVL4	(3 << 4)
#define		CNTL_RTS_AF_LVL_LO	(1 << 6)
#define		CNTL_CTS_AF_LVL_LO	(1 << 7)

#define MU_STAT		(AUX_BASE + 0x64)
#define		STAT_RX_FIFO_SYMBL	(1 << 0)
#define		STAT_TX_FIFO_SPACE	(1 << 1)
#define		STAT_RX_IDLE		(1 << 2)
#define		STAT_TX_IDLE		(1 << 3)
#define		STAT_RX_OVERRUN		(1 << 4)
#define		STAT_TX_FIFO_FULL	(1 << 5)
#define		STAT_RTS_STATUS		(1 << 6)
#define		STAT_CTS_STATUS		(1 << 7)
#define		STAT_TX_FIFO_EMPTY	(1 << 8)
#define		STAT_TX_DONE		(1 << 9)
#define		STAT_RX_FIFO_LEVEL	(15 << 16)
#define		STAT_TX_FIFO_LEVEL	(15 << 24)

#define MU_BAUD		(AUX_BASE + 0x68)

#endif /* __MINIUART_H__ */
