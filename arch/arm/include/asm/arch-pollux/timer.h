/* (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo <brian@cozybit.com>
 *
 * (C) Copyright 2010 Jeff Kent, <jakent@gmail.com>
 *
 * (C) Copyright 2007 Leapfrog, Inc.
 * Andrey Yurovsky" <yurovsky@gmail.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __POLLUX_TIMER_H__
#define __POLLUX_TIMER_H__

#include <config.h>

/* Timer base addresses */
#ifdef CONFIG_VR3520F
#define TIMER0_BASE	0xC0001800
#define TIMER1_BASE	0xC0001880
#define TIMER2_BASE	0xC0001900
#define TIMER3_BASE	0xC0001980
#define TIMER4_BASE	0xC0001A00
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_timer {
	__u32	tmrcount;
	__u32	tmrmatch;
	__u32	tmrcontrol;
	__u32	_reserved[13];
	__u32	tmrclkenb;
	__u32	tmrclkgen;
};

/* tmrcontrol */
/*
 * SELTCLK divider values are calculated from n where 2^n is the desired
 * divider
 */
#define TIMER_SELTCLK(n)	((u32) ((n) + 3) & 0x3)
#define TIMER_WDENB		((u32) 0x1 << 2)
#define TIMER_RUN		((u32) 0x1 << 3)
#define TIMER_INTENB		((u32) 0x1 << 4)
#define TIMER_INTPEND		((u32) 0x1 << 5)
#define TIMER_LDCNT		((u32) 0x1 << 6)

/* tmrclkenb */
#define TIMER_CLKGENENB		((u32) 0x1 << 2)
#define TIMER_TCLKMODE		((u32) 0x1 << 3)

/* tmrclkgen */
#define TIMER_CLKSRCSEL(x)	((u32) (x) << 1)
#define TIMER_CLKDIV(x)		((u32) (x-1) << 4)

/* convenience macro for calculating output HZ */
#define TIMER_HZ(pll_hz, clkdiv, seltclk) ((pll_hz)/(clkdiv)/(1<<seltclk))

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_TIMER_H__ */
