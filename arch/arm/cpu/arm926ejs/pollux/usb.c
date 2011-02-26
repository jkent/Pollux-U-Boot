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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm/arch/ohci.h>

#ifdef CONFIG_SYS_USB_OHCI_CPU_INIT

static struct pollux_ohci *ohci = (struct pollux_ohci *) OHCI_BASE;

#define USB_HZ_IN CONFIG_SYS_HZ_PLL0
#define USB_CLKDIV ((USB_HZ_IN + (48000000 / 2)) / 48000000)

int usb_cpu_init(void)
{
	writew((1<<OHCI_PCLKMODE) | (1<<OHCI_CLKGENENB) |
		(3<<OHCI_USBH_CLKENB), &ohci->clkenb);
	writew(((USB_CLKDIV-1)<<OHCI_CLKDIV), &ohci->clkgen);
	writel((1<<OHCI_DNPD) | (1<<OHCI_DPPD), &ohci->HcInitCfg);

	return 0;
}

int usb_cpu_stop(void)
{
	writel((1<<OHCI_DNPD) | (1<<OHCI_DPPD) | (1<<OHCI_SLEEP),
		&ohci->HcInitCfg);
	writew(0, &ohci->clkenb);
	writew(0, &ohci->clkgen);

	return 0;
}

int usb_cpu_init_fail(void)
{
	return usb_cpu_stop();
}

#endif /* CONFIG_SYS_USB_OHCI_CPU_INIT */
