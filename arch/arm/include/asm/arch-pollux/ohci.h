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

#ifndef __POLLUX_OHCI_H__
#define __POLLUX_OHCI_H__

#include <config.h>

/* NAND base address */
#ifdef CONFIG_VR3520F
#define OHCI_BASE 0xC000D000
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_ohci {
	__u32 HcRevision;
	__u32 HcControl;
	__u32 HcCommonStatus;
	__u32 HcInterruptStatus;
	__u32 HcInterruptEnable;
	__u32 HcInterruptDisable;
	__u32 HcHCCA;
	__u32 HcPeriodCurrentED;
	__u32 HcControlHeadED;
	__u32 HcControlCurrentED;
	__u32 HcBulkHeadED;
	__u32 HcBulkCurrentED;
	__u32 HcDoneHead;
	__u32 HcRmInterval;
	__u32 HcFmRemaining;
	__u32 HcFmNumber;
	__u32 HcPeriodicStart;
	__u32 HcLSThreshold;
	__u32 HcRhDescriptorA;
	__u32 HcRhDescriptorB;
	__u32 HcRhStatus;
	__u32 HcRhPortStatus1;
	__u32 HcRhPortStatus2;
	__u32 _reserved[9];
	__u32 HcInitCfg;
	__u32 _reserved2[15];
	__u32 clkenb;
	__u32 clkgen;
};

/* HcInitCfg */
#define OHCI_SLEEP			0
#define OHCI_PUSW1			1
#define OHCI_PUSW2			2
#define OHCI_DPPD			3
#define OHCI_DNPD			4

/* clkenb */
#define OHCI_USBH_CLKENB		0
#define OHCI_CLKGENENB			2
#define OHCI_PCLKMODE			3

/* clkgen */
#define OHCI_CLKSRCSEL			1
#define OHCI_CLKDIV			4

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_NAND_H__ */
