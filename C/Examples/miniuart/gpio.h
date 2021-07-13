/*
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com.
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "io.h"

#define GPFSEL1_OFFS	0x04
#define GPSET0_OFFS	0x1C
#define GPCLR0_OFFS	0x28
#define GPPUD_OFFS	0x94
#define GPPUDCLK0_OFFS	0x98

#define GPFSEL1		(GP_MMIO + GPFSEL1_OFFS)
#define GPSET0		(GP_MMIO + GPSET0_OFFS)
#define GPCLR0  	(GP_MMIO + GPCLR0_OFFS)
#define GPPUD		(GP_MMIO + GPPUD_OFFS)
#define GPPUDCLK0	(GP_MMIO + GPPUDCLK0_OFFS)

#endif /* __GPIO_H__ */
