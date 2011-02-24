/*
 * (C) Copyright 2011 Jeff Kent, <jakent@gmail.com>
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

#ifndef __POLLUX_NAND_H__
#define __POLLUX_NAND_H__

#include <config.h>

/* NAND base address */
#ifdef CONFIG_VR3520F
#define NAND_BASE 0x2C000000
#define NAND_SHADOW_BASE 0xAC000000
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_nand {
        __extension__ union {
                __u8 nfdata;
                __u16 nfdata16;
                __u32 nfdata32;
        };
        __u32 _reserved[3];
        __u8 nfcmd;
        __u8 _reserved2[7];
        __u8 nfaddr;
};

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_NAND_H__ */
