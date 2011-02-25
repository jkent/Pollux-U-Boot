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
#include <nand.h>
#include <asm/io.h>
#include <asm/arch/mcus.h>
#include <asm/arch/nand.h>

/* TODO: combine with s3c64xx? */

static struct pollux_mcus *mcus = (struct pollux_mcus *)MCUS_BASE;
static struct pollux_nand *nand = (struct pollux_nand *)CONFIG_SYS_NAND_BASE;

static void pollux_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct nand_chip *this = mtd->priv;
	int nand_cs = (int)this->priv;

	ulong ctrl = readl(&mcus->nfcontrol) & ~(1<<MCUS_NFBANK);
	if (chipnr >= 0 && nand_cs > 0)
		ctrl |= (1<<MCUS_NFBANK);
	writel(ctrl, &mcus->nfcontrol);
}

static void pollux_cmd_ctrl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		if (ctrl & NAND_CLE)
			this->IO_ADDR_W = (void __iomem *) &nand->nfcmd;
		else if (ctrl & NAND_ALE)
			this->IO_ADDR_W = (void __iomem *) &nand->nfaddr;
		else
			this->IO_ADDR_W = (void __iomem *) &nand->nfdata;
		if (ctrl & NAND_NCE)
			pollux_select_chip(mtd, (int)this->priv);
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

static int pollux_dev_ready(struct mtd_info *mtdinfo)
{
	return (readl(&mcus->nfcontrol) & (1<<MCUS_RNB)) ? 1 : 0;
}

int pollux_nand_init(struct nand_chip *this)
{
	static int chip_cs;

	this->IO_ADDR_R	= (void __iomem *) &nand->nfdata;
	this->IO_ADDR_W	= (void __iomem *) &nand->nfdata;

	this->ecc.mode = NAND_ECC_SOFT;

	this->cmd_ctrl = pollux_cmd_ctrl;
	this->dev_ready = pollux_dev_ready;
	this->select_chip = pollux_select_chip;

	this->priv = chip_cs++;

	return 0;
}
