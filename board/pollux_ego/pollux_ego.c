/*
 * (C) Copyright 2011 Jeff Kent, <jakent@gmail.com>
 *
 * (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo, <brian@cozybit.com>
 *
 * (C) Copyright 2007 Leapfrog, Inc.
 * Andrey Yurovsky <yurovsky@gmail.com>
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

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clkpwr.h>
#include <asm/arch/gpio.h>
#include <asm/arch/uart.h>

DECLARE_GLOBAL_DATA_PTR;

static struct clkpwr_regs *clkpwr = (struct clkpwr_regs *)CLKPWR_BASE;
static struct gpio_regs *gpioa = (struct gpio_regs *)GPIOA_BASE;
static struct uart_regs *uart = (struct uart_regs *)UART0_BASE;

/*
 * UART clock divider is calculated such that the default BRD corresponds to
 * the max baud rate.
 */
#if CONFIG_SYS_UART_PLL == 0
#define UART_HZ_IN CONFIG_SYS_HZ_PLL0
#elif CONFIG_SYS_UART_PLL == 1
#define UART_HZ_IN CONFIG_SYS_HZ_PLL1
#else
#error "Invalid uart PLL"
#endif
#define UARTDIV \
	DIV_ROUND(UART_HZ_IN, CONFIG_SYS_BAUDRATE_MAX*(DEFAULT_BRD + 1)*16)

int board_init(void)
{
	unsigned long tmp;

	icache_enable();

	/* PLL0 (cpu clock) 528000000 Hz */
	writel(CLKPWR_MDIV(9)|CLKPWR_PDIV(176)|CLKPWR_SDIV(0),
		&clkpwr->pllsetreg0);

	/* PLL1 (bus clock) 147461538 Hz */
	writel(CLKPWR_MDIV(13)|CLKPWR_PDIV(142)|CLKPWR_SDIV(1),
		&clkpwr->pllsetreg1);

	/* set bus and cpu clock source and dividers */
	writel(CLKPWR_CLKSELCPU0(0)|CLKPWR_CLKDIVCPU0(0)|CLKPWR_CLKDIV2CPU0(3)|
		CLKPWR_CLKSELBCLK(0)|CLKPWR_CLKDIV1BCLK(3),
		&clkpwr->clkmodereg);

	/* apply settings */
	writel(readl(&clkpwr->pwrmode)|CLKPWR_CHGPLL, &clkpwr->clkmodereg);

	/* wait for PLLs to stabalize */
	while (readl(&clkpwr->pwrmode) & CLKPWR_CHGPLL)
		;

	/* Configure UART0 TX pin (GPIOA pin 8) to be the UART TX (ALTFN1) */
	tmp = readl(&gpioa->gpioaltfn0);
	tmp &= ~GPIOALTFN0(8, 0x3);
	tmp |= GPIOALTFN0(8, GPIO_ALTFN1);
	writel(tmp, &gpioa->gpioaltfn0);

	/* ...and setup uart clocking */
	writel(UART_PCLKMODE, &uart->uartclkenb);
	writew(UART_TXPEND | UART_RXPEND | UART_ERRPEND | UART_MPEND,
		&uart->intstatusreg);
	tmp = UART_CLKSRCSEL(CONFIG_SYS_UART_PLL);
	tmp |= UART_CLKDIV(UARTDIV);
	writel(tmp,
		&uart->uartclkgen);
	writel(UART_CLKGENENB | UART_PCLKMODE, &uart->uartclkenb);

	return 0;
}

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	return 0;
}
