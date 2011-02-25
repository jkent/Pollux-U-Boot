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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*#define DEBUG*/

#define POLLUX_EGO

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_CONSOLE_INFO_QUIET
#define CONFIG_SKIP_RELOCATE_UBOOT
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE			(32 << 10)	/* 32 KiB */

/* SoC configuration */
#define CONFIG_ARM926EJS
#define CONFIG_POLLUX			/* SoC family name */
#define CONFIG_VR3520F			/* SoC name */
#define CONFIG_SYS_HZ_PLL0		528000000
#define CONFIG_SYS_HZ_PLL1		147461538
#define CONFIG_SYS_HZ			1024

#include <asm/arch/uart.h>
#include <asm/arch/nand.h>

/* memory info */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_TEXT_BASE		0x01000000

/* timer set up */
#define CONFIG_SYS_TIMER_CLKDIV		35
#define CONFIG_SYS_TIMER_SELTCLK_LOG2	2

/* serial port configuration */
#define CONFIG_S3C44B0_SERIAL
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_BAUDRATE_MAX		115200
#define CONFIG_SYS_UART_PLL		1

/* ethernet configuration */
#define CONFIG_DRIVER_DM9000
#define CONFIG_DM9000_BASE		0x84000000 /* cs1, shadow = 1 */
#define DM9000_IO			CONFIG_DM9000_BASE
#define DM9000_DATA			(CONFIG_DM9000_BASE + 4)

/* nand configuration */
#define CONFIG_NAND_POLLUX
#define CONFIG_SYS_MAX_NAND_DEVICE	2
#define CONFIG_SYS_NAND_BASE		NAND_SHADOW_BASE
#define CONFIG_SYS_NAND_QUIET_TEST
#define CONFIG_SYS_NAND_SW_ECC

/* console/printing setup */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMD_ECHO
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT		"U-Boot# "
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_CBSIZE		1024
#define CONFIG_SYS_PBSIZE 		\
	(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16

/* nand features */
#ifdef CONFIG_NAND_POLLUX
#define CONFIG_CMD_MTDPARTS
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NAND_LOCK_UNLOCK
#define CONFIG_CMD_UBI
/*#define CONFIG_MTD_DEBUG
#define CONFIG_MTD_DEBUG_VERBOSE	3*/
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_RBTREE
#endif

/* nand environment */
#ifdef CONFIG_NAND_POLLUX
#undef CONFIG_ENV_IS_NOWHERE
#undef CONFIG_ENV_SIZE
#define CONFIG_ENV_SIZE			(256 << 10)	/* 256 KiB */
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET		0x00380000
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CMD_SAVEENV
#endif /* CONFIG_NAND_POLLUX */

/* other environment */
#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_EDITENV
#define CONFIG_CMD_RUN

/* networking */
#ifdef CONFIG_DRIVER_DM9000
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_NET
#define CONFIG_NET_MULTI
#define CONFIG_NET_RETRY_COUNT		10
#endif /* CONFIG_DRIVER_DM9000 */

/* Linux interfacing */
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_SYS_BARGSIZE		1024
#define CONFIG_SYS_LOAD_ADDR		0x01800000

/* U-Boot memory configuration */
#define CONFIG_STACKSIZE		(256 << 10)	/* 256 KiB */
#define CONFIG_SYS_MALLOC_LEN		(1 << 20)	/* 1 MiB */
#define CONFIG_MAX_RAM_BANK_SIZE	(128 << 20)	/* 128 MB */
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_INIT_SP_ADDR		\
	(CONFIG_SYS_SDRAM_BASE + 0x8000 - GENERATED_GBL_DATA_SIZE)

#define CONFIG_CMD_MEMORY
#define CONFIG_SYS_MEMTEST_START	0x01800000
#define CONFIG_SYS_MEMTEST_END		0x40000000

#endif	/* __CONFIG_H */
