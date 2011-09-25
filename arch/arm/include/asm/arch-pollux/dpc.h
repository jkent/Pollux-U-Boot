/*
 * Copyright (C) 2011 Jeff Kent <jakent@gmail.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef __POLLUX_DPC_H__
#define __POLLUX_DPC_H__

#include <config.h>

/* DPC base addresses */
#ifdef CONFIG_VR3520F
#define DPC0_BASE 0xc0003000
#define DPC1_BASE 0xc0003400
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_dpc {
	__u16 _reserved;
	__u16 vencctrla;
	__u16 vencctrlb;
	__u16 _reserved2;
	__u16 vencsch;
	__u16 venchue;
	__u16 vencsat;
	__u16 venccrt;
	__u16 vencbrt;
	__u16 vencfscadjh;
	__u16 vencfscadjl;
	__u16 _reserved3[5];
	__u16 vencdacsel;
	__u16 _reserved4[15];
	__u16 vencicntl;
	__u16 _reserved5[3];
	__u16 venchsvso;
	__u16 venchsos;
	__u16 venchsoe;
	__u16 vencvsos;
	__u16 vencvsoe;
	__u16 _reserved6[21];
	__u16 htotal;
	__u16 hswidth;
	__u16 hastart;
	__u16 haend;
	__u16 vtotal;
	__u16 vswidth;
	__u16 vastart;
	__u16 vaend;
	__u16 ctrl0;
	__u16 ctrl1;
	__u16 evtotal;
	__u16 evswidth;
	__u16 evastart;
	__u16 evaend;
	__u16 ctrl2;
	__u16 vseoffset;
	__u16 vssoffset;
	__u16 evseoffset;
	__u16 evssoffset;
	__u16 delay0;
	__u16 upscalecon0;
	__u16 upscalecon1;
	__u16 upscalecon2;
	__u16 rnumgencon0;
	__u16 rnumgencon1;
	__u16 rnumgencon2;
	__u16 fdtaddr;
	__u16 frdithervalue;
	__u16 fgdithervalue;
	__u16 fbdithervalue;
	__u16 _reserved7[132];
	__u32 clkenb;
	__u32 clkgen0;
	__u32 clkgen1;
};

/* vencctrla */
#define DPC_PWDENC			7
#define DPC_FDRST			6
#define DPC_FDSEL			4
#define DPC_PED				3
#define DPC_IFMT			1
#define DPC_PHALT			0

/* venctrlb */
#define DPC_CBW				2
#define DPC_YBW				0

/* venchsvso */
#define DPC_VSOB8			6
#define DPC_HSOB10_8			3
#define DPC_HSOE10_8			0

/* ctrl0 */
#define DPC_DPCENB			15
#define DPC_ENCMODE			14
#define DPC_ENCRST			13
#define DPC_RGBMODE			12
#define DPC_INTENB			11
#define DPC_INTPEND			10
#define DPC_SCANMODE			9
#define DPC_SEAVENB			8
#define DPC_DELAYRGB			4
#define DPC_POLFIELD			2
#define DPC_POLVSYNC			1
#define DPC_POLHSYNC			0

/* ctrl1 */
#define DPC_SWAPRB			15
#define DPC_YCRANGE			13
#define DPC_FORMAT			8
#define DPC_YCORDER			6
#define DPC_BDITHER			4
#define DPC_GDITHER			2
#define DPC_RDITHER			0

/* ctrl2 */
#define DPC_CL2CYC			12
#define DPC_STNLCDBITWIDTH		9
#define DPC_LCDTYPE			8
#define DPC_PADCLKSEL			0

/* delay0 */
#define DPC_DELAYDE			8
#define DPC_DELAYVS			4
#define DPC_DELAYHS			0

/* upscalecon0 */
#define DPC_UPSCALEL			8
#define DPC_UPSCALERENB			0

/* rnumgencon2 */
#define DPC_RNUMGENENB			12
#define DPC_RNCONVALUE1			0

/* clkenb */
#define DPC_PCLKMODE			3
#define DPC_CLKGENENB			2

/* clkgen0/1 */
#define DPC_OUTCLKENB			15
#define DPC_OUTCLKDELAY			12
#define DPC_CLKDIV			4
#define DPC_CLKSRCSEL			1
#define DPC_OUTCLKINV			0

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_DPC_H__ */
