/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com.
 */

#ifndef __AUXIO_H__
#define __AUXIO_H__

#include "io.h"

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
#define		CNTL_RX_DIS_MASK	(0 << 0)
#define		CNTL_TX_ENA_MASK	(1 << 1)
#define		CNTL_TX_DIS_MASK	(0 << 1)
#define		CNTL_RTS_AFLOW_ENA_MASK	(1 << 2)
#define		CNTL_RTS_AFLOW_DIS_MASK	(0 << 2)
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

#define AUX_ENB_REG		(AUX_MMIO + AUX_ENB_REG_OFFS)
#define AUX_MU_IO_REG		(AUX_MMIO + AUX_MU_IO_REG_OFFS)
#define AUX_MU_IER_REG		(AUX_MMIO + AUX_MU_IER_REG_OFFS)
#define AUX_MU_IIR_REG		(AUX_MMIO + AUX_MU_IIR_REG_OFFS)
#define AUX_MU_LCR_REG		(AUX_MMIO + AUX_MU_LCR_REG_OFFS)
#define AUX_MU_MCR_REG		(AUX_MMIO + AUX_MU_MCR_REG_OFFS)
#define AUX_MU_LSR_REG		(AUX_MMIO + AUX_MU_LSR_REG_OFFS)
#define AUX_MU_MSR_REG		(AUX_MMIO + AUX_MU_MSR_REG_OFFS)
#define AUX_MU_SCRATCH_REG	(AUX_MMIO + AUX_MU_SCRATCH_REG_OFFS)
#define AUX_MU_CNTL_REG		(AUX_MMIO + AUX_MU_CNTL_REG_OFFS)
#define AUX_MU_STAT_REG		(AUX_MMIO + AUX_MU_STAT_REG_OFFS)
#define AUX_MU_BAUD_REG		(AUX_MMIO + AUX_MU_BAUD_REG_OFFS)

#endif /* __AUXIO_H__ */
