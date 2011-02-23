/*
 * (C) Copyright 2010 cozybit, Inc.
 * Brian Cavagnolo <brian@cozybit.com>
 *
 * (C) Copyright 2010 Jeff Kent, <jakent@gmail.com>
 *
 * (C) Copyright 2007 Leapfrog, Inc.
 * Kosta Demirev, kdemirev@yahoo.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define DEBUG

#define CONFIG_ARM926EJS
#define CONFIG_POLLUX			/* SOC family name */
#define CONFIG_VR3520F			/* SOC name */

#include <asm/arch/uart.h>
#include <asm/arch/timer.h>

/* minimal support for now, so turn lots of stuff off */
#define CONFIG_SYS_NO_FLASH
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_SKIP_RELOCATE_UBOOT
#define CONFIG_SKIP_LOWLEVEL_INIT

/* memory layout */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			0x00000000
#define PHYS_SDRAM_1_SIZE		(128 << 20)	/* 128 MiB */
#define CONFIG_SYS_GBL_DATA_SIZE	128
#define CONFIG_ENV_SIZE			8192
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128 * 1024)
#define CONFIG_STACKSIZE		(128 * 1024)
#define CONFIG_SYS_TEXT_BASE		0x01000000
#define CONFIG_SYS_LOAD_ADDR		0x00008000

/* timer set up */
#define CONFIG_SYS_TIMERBASE		TIMER0_BASE
#define CONFIG_SYS_TIMER_PLL		0
#define CONFIG_SYS_TIMER_CLKDIV		256
#define CONFIG_SYS_TIMER_SELTCLK_LOG2	3

/* clock set up */
#define CONFIG_SYS_HZ_PLL0		528000000
#define CONFIG_SYS_HZ_PLL1		147461538
#define CONFIG_SYS_HZ			TIMER_HZ(CONFIG_SYS_HZ_PLL0, \
						CONFIG_SYS_TIMER_CLKDIV, \
						CONFIG_SYS_TIMER_SELTCLK_LOG2)

/* serial port configuration */
#define CONFIG_S3C44B0_SERIAL
#define CONFIG_SYS_UART_PLL		1
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_BAUDRATE_MAX		115200

/* ethernet configuration */
#define CONFIG_CMD_NET
#define CONFIG_NET_MULTI
#define CONFIG_DRIVER_DM9000
#define CONFIG_DM9000_BASE		0x84000000 /* cs1, shadow = 1 */
#define DM9000_IO			CONFIG_DM9000_BASE
#define DM9000_DATA			(CONFIG_DM9000_BASE + 4)

/* console/printing setup */
#define CONFIG_SYS_PROMPT "=> "
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE \
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16

#define CONFIG_MAX_RAM_BANK_SIZE        (128 << 20)	/* 128 MB */

#define CONFIG_CMD_MISC

#define CONFIG_SYS_SDRAM_BASE           PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_SDRAM_BASE + 0x8000 - GENERATED_GBL_DATA_SIZE)

#endif	/* __CONFIG_H */
