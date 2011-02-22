/*********************/
/* UART Registers    */
/*********************/

#ifndef __POLLUX_HARDWARE_H__
#define __POLLUX_HARDWARE_H__

#ifndef __ASSEMBLY__

/* s3c44b0 serial driver looks for our uart definitions here in hardware.h */
#include <asm/arch/uart.h>

#define REG(b, m) *((volatile u16 *)&(((struct uart_regs *)(b))->m))

#define ULCON0		REG(UART0_BASE, lcon)
#define UCON0		REG(UART0_BASE, ucon)
#define UFCON0		REG(UART0_BASE, fcon)
#define UMCON0		REG(UART0_BASE, mcon)
#define UTRSTAT0	REG(UART0_BASE, trstatus)
#define UERSTAT0	REG(UART0_BASE, estatus)
#define UFSTAT0		REG(UART0_BASE, fstatus)
#define UMSTAT0		REG(UART0_BASE, mstatus)
#define UTXH0		REG(UART0_BASE, thb)
#define URXH0		REG(UART0_BASE, rhb)
#define UBRDIV0		REG(UART0_BASE, brd)

#define ULCON1		REG(UART1_BASE, lcon)
#define UCON1		REG(UART1_BASE, ucon)
#define UFCON1		REG(UART1_BASE, fcon)
#define UMCON1		REG(UART1_BASE, mcon)
#define UTRSTAT1	REG(UART1_BASE, trstatus)
#define UERSTAT1	REG(UART1_BASE, estatus)
#define UFSTAT1		REG(UART1_BASE, fstatus)
#define UMSTAT1		REG(UART1_BASE, mstatus)
#define UTXH1		REG(UART1_BASE, thb)
#define URXH1		REG(UART1_BASE, rhb)
#define UBRDIV1		REG(UART1_BASE, brd)

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_HARDWARE_H__ */
