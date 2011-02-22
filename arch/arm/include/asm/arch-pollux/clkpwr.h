/* (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo <brian@cozybit.com>
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

#ifndef __POLLUX_CLKPWR_H__
#define __POLLUX_CLKPWR_H__

#include <config.h>

/* CLKPWR base address */
#ifdef CONFIG_VR3520F
#define CLKPWR_BASE		0xC000F000
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct clkpwr_regs {
	u32	clkmodereg;
	u32	pllsetreg0;
	u32	pllsetreg1;
	u32	_reserved1[13];
	u32	gpiowakeupenb;
	u32	rtcwakeupenb;
	u32	gpiowakeupriseenb;
	u32	gpiowakeupfallenb;
	u32	gpiopend;
	u32	_reserved2[1];
	u32	intpendspad;
	u32	pwrrstatus;
	u32	intenb;
	u32	_reserved3[6];
	u32	pwrmode;
	u32	_reserved4[32];
	u32	padstrengthgpioal;
	u32	padstrengthgpioah;
	u32	padstrengthgpiobl;
	u32	padstrengthgpiobh;
	u32	padstrengthgpiocl;
	u32	padstrengthgpioch;
	u32	padstrengthbus;
};

/* clkmodereg */
#define CLKPWR_CLKSELCPU0(x)		((u32) (x) << 4)
#define CLKPWR_CLKDIV2CPU0(x)		((u32) ((x) - 1) << 6)
#define CLKPWR_CLKDIVCPU0(x)		((u32) ((x) - 1) << 0)
#define CLKPWR_CLKDIV1BCLK(x)		((u32) ((x) - 1) << 20)
#define CLKPWR_CLKSELBCLK(x)		((u32) (x) << 24)
#define CLKPWR_PLLPWDN1			((u32) 0x1 << 30)

/* pllsetregX */
#define CLKPWR_SDIV(x)			((u32) (x) << 0)
#define CLKPWR_MDIV(x)			((u32) (x) << 8)
#define CLKPWR_PDIV(x)			((u32) (x) << 18)

/* gpiowakeupenb */
#define CLKPWR_WKUPEN(x)		((u32) 0x1 << (x))

/* rtcwakeupenb */
#define CLKPWR_WKRTC			((u32) 0x1 << 0)

/* gpiowakeupriseenb */
#define CLKPWR_RISEWKSRC(x)		((u32) 0x1 << (x))

/* gpiowakeupfallenb */
#define CLKPWR_FALLWKSRC(x)		((u32) 0x1 << (x))

/* gpiopend */
#define CLKPWR_WKDET(x)			((u32) 0x1 << (x))

/* intpendspad */
#define CLKPWR_SCRPAD(x)		((u32) (x) & 0x7ff)
#define CLKPWR_POWERONRSTW		((u32) 0x1 << 11)
#define CLKPWR_WATCHDOGRSTW		((u32) 0x1 << 12)
#define CLKPWR_GPIORESETW		((u32) 0x1 << 13)
#define CLKPWR_BATFW			((u32) 0x1 << 14)

/* pwrrstatus */
#define CLKPWR_POWERONRSTR		((u32) 0x1 << 0)
#define CLKPWR_WATCHDOGRSTR		((u32) 0x1 << 1)
#define CLKPWR_GPIORESETR		((u32) 0x1 << 2)
#define CLKPWR_BATF			((u32) 0x1 << 3)

/* intenb */
#define CLKPWR_GPIOINTENB		((u32) 0x1 << 0)
#define CLKPWR_BATFINTENB		((u32) 0x1 << 2)

/* pwrmode */
#define CLKPWR_CURPWRMODE(x)		((u32) (x) & 0x3)
#define CLKPWR_GET_LASTPWRMODE(x)	((u32) (((x) >> 4) & (0x7)))
#define CLKPWR_SWRST			((u32) 0x1 << 12)
#define CLKPWR_GPIOSWRSTENB		((u32) 0x1 << 13)
#define CLKPWR_CHGPLL			((u32) 0x1 << 15)

/* padstrengthgpio{a,b,c}l */
#define CLKPWR_GPIOL_DRV(pin, val)	((u32) (val) << ((pin)*2))

/* padstrengthgpio{a,b,c}h */
#define CLKPWR_GPIOH_DRV(pin, val)	((u32) (val) << (((pin)-16)*2))

/* padstrengthbus */
#define CLKPWR_PVCLK_DRV(x)		((u32) (x) << 0)
#define CLKPWR_DE_DRV(x)		((u32) (x) << 2)
#define CLKPWR_HSYNC_DRV(x)		((u32) (x) << 4)
#define CLKPWR_VSYNC_DRV(x)		((u32) (x) << 6)
#define CLKPWR_STATIC_DATA_DRV(x)	((u32) (x) << 18)
#define CLKPWR_STATIC_ADDR_DRV(x)	((u32) (x) << 20)
#define CLKPWR_STATIC_CNTL_DRV(x)	((u32) (x) << 22)
#define CLKPWR_DDR_CLK_DRV(x)		((u32) (x) << 24)
#define CLKPWR_DDR_DATA_DRV(x)		((u32) (x) << 26)
#define CLKPWR_DDR_ADDR_DRV(x)		((u32) (x) << 28)
#define CLKPWR_DDR_CNTL_DRV(x)		((u32) (x) << 30)

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_CLKPWR_H__ */
