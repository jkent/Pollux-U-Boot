/*
 * (C) Copyright 2011 Jeff Kent, <jakent@gmail.com>
 *
 * (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo, <brian@cozybit.com>
 *
 * (C) Copyright 2003
 * Texas Instruments <www.ti.com>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002-2004
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * (C) Copyright 2004
 * Philippe Robin, ARM Ltd. <philippe.robin@arm.com>
 *
 * Copyright (C) 2007 Sergey Kubushyn <ksi@koi8.net>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/timer.h>

DECLARE_GLOBAL_DATA_PTR;

static struct pollux_timer *timer = (struct pollux_timer *)TIMER0_BASE;

int timer_init(void)
{
	/* configure clock source and primary divisor */
	writel(TIMER_CLKDIV(CONFIG_SYS_TIMER_CLKDIV) |
		TIMER_CLKSRCSEL(1),
		&timer->tmrclkgen);

	/* enable clock */
	writel(TIMER_CLKGENENB | TIMER_TCLKMODE, &timer->tmrclkenb);
	writel(0, &timer->tmrcount);
	writel(0xFFFFFFFF, &timer->tmrmatch);
	writel(TIMER_SELTCLK(CONFIG_SYS_TIMER_SELTCLK_LOG2) | TIMER_RUN |
		TIMER_INTPEND, &timer->tmrcontrol);

	gd->timer_rate_hz = (CONFIG_SYS_HZ_PLL1 / CONFIG_SYS_TIMER_CLKDIV /
				(1<<CONFIG_SYS_TIMER_SELTCLK_LOG2));
	gd->timer_reset_value = 0;

	return 0;
}

/*
 * timer without interrupts
 */
void reset_timer(void)
{
	gd->timer_reset_value = get_ticks();
}

/*
 * Get the current 64 bit timer tick count
 */
unsigned long long get_ticks(void)
{
	unsigned long now;

	writel(readl(&timer->tmrcontrol) | TIMER_LDCNT, &timer->tmrcontrol);
	now = readl(&timer->tmrcount);

	if (now < gd->tbl)
		gd->tbu++;
	gd->tbl = now;

	return (((unsigned long long)gd->tbu) << 32) | gd->tbl;
}

ulong get_timer(ulong base)
{
	unsigned long long timer_diff;

	timer_diff = get_ticks() - gd->timer_reset_value;

	return (timer_diff / (gd->timer_rate_hz / CONFIG_SYS_HZ)) - base;
}

void __udelay(unsigned long usec)
{
	unsigned long long endtime;

	endtime = ((unsigned long long)usec * gd->timer_rate_hz) / 1000000UL;
	endtime += get_ticks();
	while (get_ticks() < endtime)
		;
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
