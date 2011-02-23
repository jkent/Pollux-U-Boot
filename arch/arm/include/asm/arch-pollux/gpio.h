/* (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo <brian@cozybit.com>
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

#ifndef __POLLUX_GPIO_H__
#define __POLLUX_GPIO_H__

#include <config.h>

#ifdef CONFIG_VR3520F
#define GPIOA_BASE		0xC000A000
#define GPIOB_BASE		0xC000A040
#define GPIOC_BASE		0xC000A080
#endif

struct pollux_gpio {
	u32 gpioout;
	u32 gpiooutenb;
	u32 gpiodetmode0;
	u32 gpiodetmode1;
	u32 gpiointenb;
	u32 gpiodet;
	u32 gpiopad;
	u32 gpiopuenb;
	u32 gpioaltfn0;
	u32 gpioaltfn1;
};

/* gpioout */
#define GPIOOUT(pin)		((u32) 0x1 << (pin))

/* gpiooutenb */
#define GPIOOUTENB(pin)		((u32) 0x1 << (pin))

/* gpiodetmode{0,1} */
enum gpio_interrupt_mode {
	GPIO_IMODE_LOW_LEVEL		= 0,
	GPIO_IMODE_HIGH_LEVEL		= 1,
	GPIO_IMODE_FALLING_EDGE		= 2,
	GPIO_IMODE_RISING_EDGE		= 3,
};
#define GPIODETMODE0(pin, val)	((u32) (val) << ((pin)*2))
#define GPIODETMODE1(pin, val)	((u32) (val) << (((pin) - 16)*2))

/* gpiointenb */
#define GPIOINTENB(pin)		((u32) 0x1 << (pin))

/* gpiodet */
#define GPIODET(pin)		((u32) 0x1 << (pin))

/* gpiopad */
#define GPIOPAD(pin)		((u32) 0x1 << (pin))

/* gpiopuenb */
#define GPIOPUENB(pin)		((u32) 0x1 << (pin))

/* gpioaltfn{0,1} */
enum gpio_functions {
	GPIO_FN		= 0,
	GPIO_ALTFN1	= 1,
	GPIO_ALTFN2	= 2,
};
#define GPIOALTFN0(pin, cfg)	((cfg) << ((pin)*2))
#define GPIOALTFN1(pin, cfg)	((cfg) << (((pin) - 16)*2))

#endif /* __POLLUX_GPIO_H__ */
