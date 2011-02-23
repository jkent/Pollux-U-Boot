/* 
 * (C) Copyright 2010 Jeff Kent, <jakent@gmail.com>
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

#ifndef __POLLUX_MCUS_H__
#define __POLLUX_MCUS_H__

#include <config.h>

/* MCUS base address */
#ifdef CONFIG_VR3520F
#define MCUS_BASE 0xC0015800
#endif

#ifndef __ASSEMBLY__
#include <asm/types.h>

struct pollux_mcus {
	__u32	bw;
	__u32	timeacs;
	__u32	timecos;
	__u32	timeaccl;
	__u32	timeacch;
	__u32	timesaccl;
	__u32	timesacch;
	__u32	_reserved[2];
	__u32	timecoh;
	__u32	timecah;
	__u32	burstl;
	__u32	bursth;
	__u32	wait;
	__u32	_reserved2[15];
	__u32	nfcontrol;
	__u32	nfeccl;
	__u32	nfecch;
	__u32	nforgeccl;
	__u32	nforgecch;
	__u32	nfcnt;
	__u32	nfeccstatus;
	__u32	nfsyndrome31;
	__u32	nfsyndrome75;	
};

/* general use */
#define MCUS_0CYCLE			3
#define MCUS_1CYCLE			0
#define MCUS_2CYCLE			1
#define MCUS_3CYCLE			2

#define MCUS_8BIT			0
#define MCUS_16BIT			1

#define MCUS_0BYTE			0
#define MCUS_4BYTE			1
#define MCUS_8BYTE			2
#define MCUS_16BYTE			3

#define MCUS_HIGH			0
#define MCUS_LOW			1

#define MCUS_OFF			0
#define MCUS_ON				1

/* bw */
#define MCUS_SR9BW			9
#define MCUS_SR8BW			8
#define MCUS_SR7BW			7
#define MCUS_SR6BW			6
#define MCUS_SR5BW			5
#define MCUS_SR4BW			4
#define MCUS_SR3BW			3
#define MCUS_SR2BW			2
#define MCUS_SR1BW			1
#define MCUS_SR0BW			0

/* timeacs */
#define MCUS_TACS11			22
#define MCUS_TACS9			18
#define MCUS_TACS8			16
#define MCUS_TACS7			14
#define MCUS_TACS6			12
#define MCUS_TACS5			10
#define MCUS_TACS4			8
#define MCUS_TACS3			6
#define MCUS_TACS2			4
#define MCUS_TACS1			2
#define MCUS_TACS0			0

/* timecos */
#define MCUS_TCOS11			22
#define MCUS_TCOS9			18
#define MCUS_TCOS8			16
#define MCUS_TCOS7			14
#define MCUS_TCOS6			12
#define MCUS_TCOS5			10
#define MCUS_TCOS4			8
#define MCUS_TCOS3			6
#define MCUS_TCOS2			4
#define MCUS_TCOS1			2
#define MCUS_TCOS0			0

/* timeaccl */
#define MCUS_TACC7			28
#define MCUS_TACC6			24
#define MCUS_TACC5			20
#define MCUS_TACC4			16
#define MCUS_TACC3			12
#define MCUS_TACC2			8
#define MCUS_TACC1			4
#define MCUS_TACC0			0

/* timeacch */
#define MCUS_TACC11			12
#define MCUS_TACC9			4
#define MCUS_TACC8			0

/* timesaccl */
#define MCUS_TSACC7			28
#define MCUS_TSACC6			24
#define MCUS_TSACC5			20
#define MCUS_TSACC4			16
#define MCUS_TSACC3			12
#define MCUS_TSACC2			8
#define MCUS_TSACC1			4
#define MCUS_TSACC0			0

/* timesacch */
#define MCUS_TSACC11			12
#define MCUS_TSACC9			4
#define MCUS_TSACC8			0

/* timecoh */
#define MCUS_TCOH11			22
#define MCUS_TCOH9			18
#define MCUS_TCOH8			16
#define MCUS_TCOH7			14
#define MCUS_TCOH6			12
#define MCUS_TCOH5			10
#define MCUS_TCOH4			8
#define MCUS_TCOH3			6
#define MCUS_TCOH2			4
#define MCUS_TCOH1			2
#define MCUS_TCOH0			0

/* timecah */
#define MCUS_TCAH11			22
#define MCUS_TCAH9			18
#define MCUS_TCAH8			16
#define MCUS_TCAH7			14
#define MCUS_TCAH6			12
#define MCUS_TCAH5			10
#define MCUS_TCAH4			8
#define MCUS_TCAH3			6
#define MCUS_TCAH2			4
#define MCUS_TCAH1			2
#define MCUS_TCAH0			0

/* burstl */
#define MCUS_BWRITE7			30
#define MCUS_BREAD7			28
#define MCUS_BWRITE6			26
#define MCUS_BREAD6			24
#define MCUS_BWRITE5			22
#define MCUS_BREAD5			20
#define MCUS_BWRITE4			18
#define MCUS_BREAD4			16
#define MCUS_BWRITE3			14
#define MCUS_BREAD3			12
#define MCUS_BWRITE2			10
#define MCUS_BREAD2			8
#define MCUS_BWRITE1			6
#define MCUS_BREAD1			4
#define MCUS_BWRITE0			2
#define MCUS_BREAD0			0

/* bursth */
#define MCUS_BWRITE9			6
#define MCUS_BREAD9			4
#define MCUS_BWRITE8			2
#define MCUS_BREAD8			0

/* wait */
#define MCUS_WAITENB9			19
#define MCUS_WAITPOL9			18
#define MCUS_WAITENB8			17
#define MCUS_WAITPOL8			16
#define MCUS_WAITENB7			15
#define MCUS_WAITPOL7			14
#define MCUS_WAITENB6			13
#define MCUS_WAITPOL6			12
#define MCUS_WAITENB5			11
#define MCUS_WAITPOL5			10
#define MCUS_WAITENB4			9
#define MCUS_WAITPOL4			8
#define MCUS_WAITENB3			7
#define MCUS_WAITPOL3			6
#define MCUS_WAITENB2			5
#define MCUS_WAITPOL2			4
#define MCUS_WAITENB1			3
#define MCUS_WAITPOL1			2
#define MCUS_WAITENB0			1
#define MCUS_WAITPOL0			0

/* nfcontrol */
#define MCUS_IRQPEND			15
#define MCUS_ECCRST			11
#define MCUS_RNB			9
#define MCUS_IRQENB			8
#define MCUS_NFBOOTENB			5
#define MCUS_NFTYPE			3
#define MCUS_NFBANK			0

/* nfcnt */
#define MCUS_NFWRCNT			16
#define MCUS_NFRDCNT			0

/* nfeccstatus */
#define MCUS_NFCHECKERROR		2
#define MCUS_NFECCDECDONE		1
#define MCUS_NFECCENCDONE		0

/* nfsyndrome31 */
#define MCUS_SYNDROME3			13
#define MCUS_SYNDROME1			0

/* nfsyndrome75 */
#define MCUS_SYNDROME7			13
#define MCUS_SYNDROME5			0

#endif /* __ASSEMBLY__ */

#endif /* __POLLUX_MCUS_H__ */
