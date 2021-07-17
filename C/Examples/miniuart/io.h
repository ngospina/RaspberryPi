/*
 * Based on:
 * Raspberry PI Remote Serial Protocol.
 * Copyright 2012 Jamie Iles, jamie@jamieiles.com.
 * Licensed under GPLv2.
 *
 * Copyright 2021 Gerardo Ospina, ngospina@gmail.com.
 */

#ifndef __IO_H__
#define __IO_H__

#define SYSTEM_CLOCK_FREQUENCY	250000000

#define IO_BASE	0x20000000

#define GPIO_BASE	(IO_BASE + 0x200000)
#define AUX_BASE	(IO_BASE + 0x215000)

static inline void writel(unsigned long addr, unsigned long v)
{
	*(volatile unsigned long *)addr = v;
}

static inline unsigned long readl(unsigned long addr)
{
	return *(volatile unsigned long *)addr;
}

#endif /* __IO_H__ */
