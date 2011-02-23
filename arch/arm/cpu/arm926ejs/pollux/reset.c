/*
 * (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo <brian@cozybit.com>
 *
 * (C) Copyright 2010 Jeff Kent, <jakent@gmail.com>
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
#include <asm/arch/clkpwr.h>

static struct pollux_clkpwr *clkpwr = (struct pollux_clkpwr *)CLKPWR_BASE;

void reset_cpu(ulong ignored)
{
	unsigned long tmp;
	tmp = readl(&clkpwr->pwrmode);
	tmp |= CLKPWR_GPIOSWRSTENB;
	writel(tmp, &clkpwr->pwrmode);
	tmp |= CLKPWR_SWRST;
	writel(tmp, &clkpwr->pwrmode);

	while (1)
		/* Never reached */
		;
}
