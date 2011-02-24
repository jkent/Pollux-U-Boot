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

#ifndef __POLLUX_ALIVE_H__
#define __POLLUX_ALIVE_H__

#include <config.h>

/* ALIVE base address */
#ifdef CONFIG_VR3520F
#define ALIVE_BASE 0xC0019000
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_alive {
	__u32 pwrgate;
	__u32 gpiorst;
	__u32 gpioset;
	__u32 gpioread;
	__u32 scratchrst;
	__u32 scratchset;
	__u32 scratchread;
};

/* pwrgate */
#define ALIVE_NPOWERGATING		0

/* gpiorst/set/read */
#define ALIVE_VDDPWRTOGGLE		8
#define ALIVE_VDDPWRON			7
#define ALIVE_GPIO6			6
#define ALIVE_GPIO5			5
#define ALIVE_GPIO4			4
#define ALIVE_GPIO3			3
#define ALIVE_GPIO2			2
#define ALIVE_GPIO1			1
#define ALIVE_GPIO0			0

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_ALIVE_H__ */
