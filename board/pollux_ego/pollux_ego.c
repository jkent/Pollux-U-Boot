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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include <common.h>
#include <config.h>
#include <nand.h>
#include <netdev.h>
#include <asm/io.h>
#include <asm/arch/alive.h>
#include <asm/arch/clkpwr.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mcus.h>
#include <asm/arch/uart.h>

DECLARE_GLOBAL_DATA_PTR;

static struct pollux_alive *alive = (struct pollux_alive *)ALIVE_BASE;
static struct pollux_clkpwr *clkpwr = (struct pollux_clkpwr *)CLKPWR_BASE;
static struct pollux_gpio *gpioa = (struct pollux_gpio *)GPIOA_BASE;
static struct pollux_mcus *mcus = (struct pollux_mcus *)MCUS_BASE;
static struct pollux_uart *uart = (struct pollux_uart *)UART0_BASE;

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

#define WP(n) \
	if (n) { \
		writel(1, &alive->pwrgate); \
		writel(0, &alive->gpioset); \
		writel((1<<ALIVE_GPIO0), &alive->gpiorst); \
		writel(0, &alive->gpiorst); \
		writel(0, &alive->pwrgate); \
	}else { \
		writel(1, &alive->pwrgate); \
		writel(0, &alive->gpiorst); \
		writel((1<<ALIVE_GPIO0), &alive->gpioset); \
		writel(0, &alive->gpioset); \
		writel(0, &alive->pwrgate); \
	}

int board_init(void)
{
	unsigned long tmp;

	icache_enable();

	gd->bd->bi_arch_number = MACH_TYPE_DIDJ;
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	/* set cpu clock source and dividers */
	tmp = readl(&clkpwr->clkmodereg) & ~(0x3FF);
	writel(tmp | CLKPWR_CPUPLL(0) | CLKPWR_CPUDIV(1) | CLKPWR_AHBDIV(4),
		&clkpwr->clkmodereg);

	/* set bus clock source and divider */
	tmp = readl(&clkpwr->clkmodereg) & ~(0x3F<<20);
	writel(tmp | CLKPWR_BCLKPLL(0) | CLKPWR_BCLKDIV(4),
		&clkpwr->clkmodereg);

	/* PLL0 (cpu clock) 528000000 Hz */
	writel(CLKPWR_PDIV(9) | CLKPWR_MDIV(176) | CLKPWR_SDIV(0),
		&clkpwr->pllsetreg0);

	/* enable PLL1 */
	writel(readl(&clkpwr->clkmodereg) & ~CLKPWR_PLLPWDN1,
		&clkpwr->clkmodereg);

	/* PLL1 (bus clock) 147461538 Hz */
	writel(CLKPWR_PDIV(13) | CLKPWR_MDIV(142) | CLKPWR_SDIV(1),
		&clkpwr->pllsetreg1);

	/* apply settings */
	writel(readl(&clkpwr->pwrmode)|CLKPWR_CHGPLL, &clkpwr->pwrmode);

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

#ifdef CONFIG_NET_MULTI
int board_eth_init(bd_t *bis)
{
	int rc = 0;

#ifdef CONFIG_DRIVER_DM9000
	ulong tmp;

	/* Configure 0x84000000 space */
	/* TODO: tune settings and make macros/functions */
	tmp = readl(&mcus->bw) & ~(1<<MCUS_SR1BW);
	writel(tmp | (MCUS_16BIT<<MCUS_SR1BW), &mcus->bw);

	tmp = readl(&mcus->timeacs) & ~(3<<MCUS_TACS1);
	writel(tmp | (MCUS_3CYCLE<<MCUS_TACS1), &mcus->timeacs);

	tmp = readl(&mcus->timecos) & ~(3<<MCUS_TCOS1);
	writel(tmp | (MCUS_3CYCLE<<MCUS_TCOS1), &mcus->timecos);

	tmp = readl(&mcus->timeaccl) & ~(15<<MCUS_TACC1);
	writel(tmp | (15<<MCUS_TACC1), &mcus->timeaccl);

	tmp = readl(&mcus->timesaccl) & ~(15<<MCUS_TSACC1);
	writel(tmp | (15<<MCUS_TSACC1), &mcus->timesaccl);

	tmp = readl(&mcus->timecoh) & ~(3<<MCUS_TCOH1);
	writel(tmp | (MCUS_3CYCLE<<MCUS_TCOH1), &mcus->timecoh);

	tmp = readl(&mcus->timecah) & ~(3<<MCUS_TCAH1);
	writel(tmp | (MCUS_3CYCLE<<MCUS_TCAH1), &mcus->timecah);

	tmp = readl(&mcus->burstl) & ~((3<<MCUS_BREAD1) | (3<<MCUS_BWRITE1));
	writel(tmp | (MCUS_0BYTE<<MCUS_BREAD1) | (MCUS_0BYTE<<MCUS_BWRITE1),
		&mcus->burstl);

	tmp = readl(&mcus->wait) & ~((1<<MCUS_WAITPOL1) | (1<<MCUS_WAITENB1));
	writel(tmp | (MCUS_LOW<<MCUS_WAITPOL1) | (MCUS_OFF<<MCUS_WAITENB1),
		&mcus->wait);

	rc += dm9000_initialize(bis);
#endif
	return rc;
}
#endif

#ifdef CONFIG_NAND_POLLUX
int pollux_nand_init(struct nand_chip *this);

int board_nand_init(struct nand_chip *nand)
{
	WP(0);

	writel(readl(&mcus->nfcontrol) | (1<<MCUS_NFBANK), &mcus->nfcontrol);

	return pollux_nand_init(nand);
}
#endif
