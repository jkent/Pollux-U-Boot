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

#ifndef __POLLUX_MLC_H__
#define __POLLUX_MLC_H__

#include <config.h>

/* DPC base addresses */
#ifdef CONFIG_VR3520F
#define MLC0_BASE 0xC0004000
#define MLC1_BASE 0xC0004400
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_mlc {
	__u32 controlt;
	__u32 screensize;
	__u32 bgcolor;
	__u32 leftright0;
	__u32 topbottom0;
	__u32 leftright0_0;
	__u32 topbottom0_0;
	__u32 leftright0_1;
	__u32 topbottom0_1;
	__u32 control0;
	__u32 hstride0;
	__u32 vstride0;
	__u32 tpcolor0;
	__u32 invcolor0;
	__u32 address0;
	__u32 palette0;
	__u32 leftright1;
	__u32 topbottom1;
	__u32 leftright1_0;
	__u32 topbottom1_0;
	__u32 leftright1_1;
	__u32 topbottom1_1;
	__u32 control1;
	__u32 hstride1;
	__u32 vstride1;
	__u32 tpcolor1;
	__u32 invcolor1;
	__u32 address1;
	__u32 palette1;
	__u32 leftright2;
	__u32 topbottom2;
	__u32 control2;
	__u32 vstride2;
	__u32 tpcolor2;
	__u32 _reserved;
	__u32 address2;
	__u32 addresscb;
	__u32 addresscr;
	__u32 vstridecb;
	__u32 vstridecr;
	__u32 hscale;
	__u32 vscale;
	__u32 luenh;
	__u32 chenh0;
	__u32 chenh1;
	__u32 chenh2;
	__u32 chenh3;
	__u32 _reserved2[193];
	__u32 clkenb;
};

/* controlt */
#define MLC_PIXELBUFFER_PWD		11
#define MLC_PIXELBUFFER_SLD		10
#define MLC_PRIORITY			8
#define MLC_TDIRTYFLAG			3
#define MLC_MLCENB			1
#define MLC_FIELDENB			0

/* screensize */
#define MLC_SCREENHEIGHT		16
#define MLC_SCREENWIDTH			0

/* leftright* */
#define MLC_INVALIDENB			28
#define MLC_LEFT			16
#define MLC_RIGHT			0

/* topbottom* */
#define MLC_TOP				16
#define MLC_BOTTOM			0

/* control0/1/2 */
#define MLC_FORMAT			16
#define MLC_PALETTEPWD			15
#define MLC_LINEBUFFER_PWD		15
#define MLC_PALETTESLD			14
#define MLC_LINEBUFFER_SLMD		14
#define MLC_LOCKSIZE			12
#define MLC_LAYERENB			5
#define MLC_DIRTYFLAG			4
#define MLC_BLENDENB			2
#define MLC_INVENB			1
#define MLC_TPENB			0

/* tpcolor0/1/2 */
#define MLC_ALPHA			28
#define MLC_TPCOLOR			0

/* palette0/1 */
#define MLC_PALETTEADDR			24
#define MLC_PALETTEDATA			0

/* hscale */
#define MLC_HFILTERENB			28
#define MLC_HSCALE			0

/* vscale */
#define MLC_VILTERENB			28
#define MLC_VSCALE			0

/* luenh */
#define MLC_BRIGHTNESS			8
#define MLC_CONTRAST			0

/* chenh0/1/2/3 */
#define MLC_HUECRB			24
#define MLC_HUECRA			16
#define MLC_HUECBB			8
#define MLC_HUECBA			0

/* clkenb */
#define MLC_PCLKMODE			3
#define MLC_BCLKMODE			0

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_MLC_H__ */
