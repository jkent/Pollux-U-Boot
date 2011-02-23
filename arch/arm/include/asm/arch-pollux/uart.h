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

#ifndef __POLLUX_UART_H__
#define __POLLUX_UART_H__

#include <config.h>

/* UART base addresses */
#ifdef CONFIG_VR3520F
#define UART0_BASE		0xC0016000
#define UART1_BASE		0xC0016080
#define UART2_BASE		0xC0016800
#define UART3_BASE		0xC0016880
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_uart {
	__u16	lcon;
	__u16	ucon;
	__u16	fcon;
	__u16	mcon;
	__u16	trstatus;
	__u16	estatus;
	__u16	fstatus;
	__u16	mstatus;
	__u16	thb;
	__u16	rhb;
	__u16	brd;
	__u16	timeoutreg;
	__u16	intstatusreg;
	__u16	_reserved[19];
	__u32	uartclkenb;
	__u32	uartclkgen;
};

/* lcon */
#define UART_WORD_LEN(x)	((u16) ((x) - 5) << 0)
#define UART_STOPBIT(x)		((u16) ((x) - 1) << 2)
#define UART_PARITY_NONE	((u16) 0x0 << 5)
#define UART_PARITY_ODD		((u16) 0x4 << 5)
#define UART_PARITY_EVEN	((u16) 0x5 << 5)
#define UART_PARITY_ONE		((u16) 0x6 << 5)
#define UART_PARITY_ZERO	((u16) 0x7 << 5)
#define UART_SIR_MODE		((u16) 0x1 << 6)
#define UART_SYNC_PENDCLR	((u16) 0x1 << 7)

/* ucon */
#define UART_RX_MODE_DISABLE	((u16) 0x0 << 0)
#define UART_RX_MODE_INTPOLL	((u16) 0x1 << 0)
#define UART_RX_MODE_DMA	((u16) 0x2 << 0)
#define UART_TX_MODE_DISABLE	((u16) 0x0 << 2)
#define UART_TX_MODE_INTPOLL	((u16) 0x1 << 2)
#define UART_TX_MODE_DMA	((u16) 0x2 << 2)
#define UART_SEND_BREAK		((u16) 0x1 << 4)
#define UART_LOOPBACK		((u16) 0x1 << 5)
#define UART_RX_ERRSTATUS	((u16) 0x1 << 6)
#define UART_RX_TIMEOUT		((u16) 0x1 << 7)
#define UART_RX_INT		((u16) 0x1 << 8)
#define UART_TX_INT		((u16) 0x1 << 9)

/* fcon */
#define UART_FIFO_EN			((u16) 0x1 << 0)
#define UART_RX_FIFO_RESET		((u16) 0x1 << 1)
#define UART_TX_FIFO_RESET		((u16) 0x1 << 2)
#define UART_RX_FIFO_TRIG(x)		((u16) ((x)>>2) << 4)
#define UART_TX_FIFO_TRIG(x)		((u16) ((x)>>2) << 6)

/* mcon */
#define UART_RTS_ACTIVE		((u16) 0x1 << 0)
#define UART_DTR_ACTIVE		((u16) 0x1 << 1)
#define UART_AFC		((u16) 0x1 << 4)
#define UART_SCTXENB		((u16) 0x1 << 5)
#define UART_SCRXENB		((u16) 0x1 << 6)
#define UART_HALF_CH_ENB	((u16) 0x1 << 7)

/* trstatus */
#define UART_RXBUF_READY	((u16) 0x1 << 0)
#define UART_TXBUF_EMPTY	((u16) 0x1 << 1)
#define UART_TX_EMPTY		((u16) 0x1 << 2)

/* estatus */
#define UART_OVERRUN_ERR	((u16) 0x1 << 0)
#define UART_PARITY_ERR		((u16) 0x1 << 1)
#define UART_FRAME_ERR		((u16) 0x1 << 2)
#define UART_BREAK_DETECT	((u16) 0x1 << 3)

/* fstatus */
#define UART_RX_FIFO_COUNT(x)	(((x) >> 0) & 0xf)
#define UART_TX_FIFO_COUNT(x)	(((x) >> 4) & 0xf)
#define UART_RX_FIFO_FULL	((u16) 0x1 << 8)
#define UART_TX_FIFO_FULL	((u16) 0x1 << 9)
#define UART_TX_FIFO_ERROR	((u16) 0x1 << 10)

/* mstatus */
#define UART_CTS		((u16) 0x1 << 0)
#define UART_DSR		((u16) 0x1 << 1)
#define UART_RI			((u16) 0x1 << 2)
#define UART_DCD		((u16) 0x1 << 3)
#define UART_DELTA_CTS		((u16) 0x1 << 4)
#define UART_DELTA_DSR		((u16) 0x1 << 5)
#define UART_DELTA_RI		((u16) 0x1 << 6)
#define UART_DELTA_DCD		((u16) 0x1 << 7)

/* brd */
#define DEFAULT_BRD	1
#define BRD(br) (DIV_ROUND(CONFIG_SYS_BAUDRATE_MAX*(DEFAULT_BRD + 1), br) - 1)

/* intstatus */
#define UART_TXPEND		((u16) 0x1 << 0)
#define UART_RXPEND		((u16) 0x1 << 1)
#define UART_ERRPEND		((u16) 0x1 << 2)
#define UART_MPEND		((u16) 0x1 << 3)
#define UART_IRQTXENB		((u16) 0x1 << 4)
#define UART_IRQRXENB		((u16) 0x1 << 5)
#define UART_ERRENB		((u16) 0x1 << 6)
#define UART_MENB		((u16) 0x1 << 7)

/* uartclkenb */
#define UART_CLKGENENB		((u32) 0x1 << 2)
#define UART_PCLKMODE		((u32) 0x1 << 3)

/* uartclkgen */
#define UART_CLKSRCSEL(x)	((u32) (x) << 1)
#define UART_CLKDIV(x)		((u32) (x-1) << 4)

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_UART_H__ */
