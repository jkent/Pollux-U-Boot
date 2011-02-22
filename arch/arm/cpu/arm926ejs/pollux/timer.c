/*
 * (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo, <brian@cozybit.com>
 *
 * (C) Copyright 2010 Jeff Kent, <jakent@gmail.com>
 *
 * (C) Copyright 2008
 * Texas Instruments
 *
 * Richard Woodruff <r-woodruff2@ti.com>
 * Syed Moahmmed Khasim <khasim@ti.com>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/timer.h>

static struct timer_regs *timer = (struct timer_regs *)CONFIG_SYS_TIMERBASE;
static ulong timestamp;
static ulong lastinc;

/* Calculate the required clock divider to achieve CONFIG_SYS_HZ */
#if CONFIG_SYS_TIMER_PLL == 0
#define TIMER_HZ_IN CONFIG_SYS_HZ_PLL0
#elif CONFIG_SYS_TIMER_PLL == 1
#define TIMER_HZ_IN CONFIG_SYS_HZ_PLL1
#else
#error "Invalid timer PLL"
#endif

#define TIMER_CLOCK	(TIMER_HZ_IN / CONFIG_SYS_TIMER_CLKDIV \
			 / (1<<CONFIG_SYS_TIMER_SELTCLK_LOG2))

#define TIMER_LOAD_VAL 0xffffffff

int timer_init(void)
{
	/* configure clock source and primary divisor */
	writel(TIMER_CLKDIV(CONFIG_SYS_TIMER_CLKDIV) |
		TIMER_CLKSRCSEL(CONFIG_SYS_TIMER_PLL),
		&timer->tmrclkgen);

	/* enable clock */
	writel(TIMER_CLKGENENB | TIMER_TCLKMODE, &timer->tmrclkenb);
	writel(0, &timer->tmrcount);
	writel(TIMER_LOAD_VAL, &timer->tmrmatch);
	writel(TIMER_SELTCLK(CONFIG_SYS_TIMER_SELTCLK_LOG2) | TIMER_RUN |
		TIMER_INTPEND, &timer->tmrcontrol);

	/* init the timestamp and lastinc value */
	reset_timer_masked();

	return 0;
}

/*
 * timer without interrupts
 */
void reset_timer(void)
{
	reset_timer_masked();
}

ulong get_timer(ulong base)
{
	return get_timer_masked() - base;
}

void set_timer(ulong t)
{
	timestamp = t;
}

static inline ulong read_timer(void)
{
	writel(readl(&timer->tmrcontrol) | TIMER_LDCNT, &timer->tmrcontrol);
	return readl(&timer->tmrcount);
}

/* delay x useconds */
void __udelay(unsigned long usec)
{
	long tmo = usec * (CONFIG_SYS_HZ / 1000) / 1000;
	unsigned long now, last;

	last = read_timer();

	while (tmo > 0) {
		now = read_timer();
		if (last > now) /* count up timer overflow */
			tmo -= TIMER_LOAD_VAL - last + now;
		else
			tmo -= now - last;
		last = now;
	}
}

void reset_timer_masked(void)
{
	/* reset time, capture current incrementer value time */
	lastinc = read_timer();
	timestamp = 0;		/* start "advancing" time stamp from 0 */
}

ulong get_timer_masked(void)
{
	ulong now;

	/* current tick value */
	now = read_timer();

	if (now >= lastinc)	/* normal mode (non roll) */
		/* move stamp fordward with absoulte diff ticks */
		timestamp += (now - lastinc);
	else	/* we have rollover of incrementer */
		timestamp += (TIMER_LOAD_VAL - lastinc) + now;
	lastinc = now;
	return timestamp;
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On ARM it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
