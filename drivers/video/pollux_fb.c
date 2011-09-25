#include <common.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mlc.h>
#include <asm/arch/dpc.h>
#include <video_fb.h>
//#include "videomodes.h"

DECLARE_GLOBAL_DATA_PTR;

#define VIDEO_MEM_SIZE		0x200000

static GraphicDevice pollux_video;

void init_pvd(void)
{
	struct pollux_gpio *gpioa = (struct pollux_gpio *) GPIOA_BASE;
	struct pollux_gpio *gpiob = (struct pollux_gpio *) GPIOB_BASE;
	u32 tmp;

	/* PVD0-17 */
	tmp = readl(&gpioa->gpioaltfn0) & 0xffff0000;
	writel(tmp | 0x00005555, &gpioa->gpioaltfn0);
	tmp = readl(&gpiob->gpioaltfn1) & 0xfff00000;
	writel(tmp | 0x00055555, &gpiob->gpioaltfn1);
}

void init_backlight(void)
{
	struct pollux_gpio *gpioa = (struct pollux_gpio *) GPIOA_BASE;
	struct pollux_gpio *gpioc = (struct pollux_gpio *) GPIOC_BASE;
	u32 tmp;

	/* PWM pin (low active) */
	tmp = readl(&gpioa->gpiooutenb) & 0xbfffffff;
	writel(tmp | 0x40000000, &gpioa->gpiooutenb);
	tmp = readl(&gpioa->gpioout) & 0xbfffffff;
	writel(tmp | 0x00000000, &gpioa->gpioout);

	/* LCD power */
	tmp = readl(&gpioc->gpiooutenb) & 0xffffddff;
	writel(tmp | 0x00002200, &gpioc->gpiooutenb);
	tmp = readl(&gpioc->gpioout) & 0xffffddff;
	writel(tmp | 0x00002200, &gpioc->gpioout);
}

void init_dpc(void)
{
	struct pollux_dpc *dpc = (struct pollux_dpc *) DPC0_BASE;

	init_pvd();

	writew(879, &dpc->htotal);
	writew(69, &dpc->hswidth);
	writew(72, &dpc->hastart);
	writew(872, &dpc->haend);
	writew(495, &dpc->vtotal);
	writew(9, &dpc->vswidth);
	writew(11, &dpc->vastart);
	writew(491, &dpc->vaend);

	writew(0x9400, &dpc->ctrl0);
	writew(0x2200, &dpc->ctrl1);
	/*writew(0x0000, &dpc->evtotal);
	writew(0x0000, &dpc->evswidth);
	writew(0x0000, &dpc->evastart);
	writew(0x0000, &dpc->evaend);*/
	writew(0x0000, &dpc->ctrl2);

	/*writew(0x0000, &dpc->vseoffset);
	writew(0x0000, &dpc->vssoffset);
	writew(0x0000, &dpc->evseoffset);
	writew(0x0000, &dpc->evssoffset);*/

	writew(0x0777, &dpc->delay0);

	/*writew(0x0000, &dpc->rnumgencon0);
	writew(0x0000, &dpc->rnumgencon1);
	writew(0x0000, &dpc->rnumgencon2);*/

	/*writew(0x0000, &dpc->fdtaddr);
	writew(0x0000, &dpc->frdithervalue);
	writew(0x0000, &dpc->fgdithervalue);
	writew(0x0000, &dpc->fbdithervalue);*/

	writel(0x00000004, &dpc->clkenb);
	writel(0x00000042, &dpc->clkgen0);
	writel(0x0000000E, &dpc->clkgen1);
}

void init_mlc(u32 addr)
{
	struct pollux_mlc *mlc = (struct pollux_mlc *) MLC0_BASE;

	writel(0x01DF031F, &mlc->screensize);
	writel(0x00000000, &mlc->bgcolor);
	writel(0x0000031F, &mlc->leftright0);
	writel(0x000001DF, &mlc->topbottom0);
	writel(0x00000000, &mlc->leftright0_0);
	writel(0x00000000, &mlc->topbottom0_0);
	writel(0x00000000, &mlc->leftright0_1);
	writel(0x00000000, &mlc->topbottom0_1);
	writel(0x00000002, &mlc->hstride0);
	writel(0x00000640, &mlc->vstride0);
	writel(0x00000000, &mlc->tpcolor0);
	writel(0x00000000, &mlc->invcolor0);
	writel(addr, &mlc->address0);
/*	writel(0x00000000, &mlc->palette0);
	writel(0x00000000, &mlc->leftright1);
	writel(0x00000000, &mlc->topbottom1);
	writel(0x00000000, &mlc->leftright1_0);
	writel(0x00000000, &mlc->topbottom1_0);
	writel(0x00000000, &mlc->leftright1_1);
	writel(0x00000000, &mlc->topbottom1_1);
	writel(0x00000000, &mlc->vstride1);
	writel(0x00000000, &mlc->vstride1);
	writel(0x00000000, &mlc->tpcolor1);
	writel(0x00000000, &mlc->invcolor1);
	writel(0x00000000, &mlc->address1);
	writel(0x00000000, &mlc->palette1);
	writel(0x00000000, &mlc->leftright2);
	writel(0x00000000, &mlc->topbottom2);
	writel(0x00000000, &mlc->vstride2);
	writel(0x00000000, &mlc->tpcolor2);
	writel(0x00000000, &mlc->address2);
	writel(0x00000000, &mlc->addresscb);
	writel(0x00000000, &mlc->addresscr);
	writel(0x00000000, &mlc->hscale);
	writel(0x00000000, &mlc->vscale);
	writel(0x00000000, &mlc->luenh);
	writel(0x00000000, &mlc->chenh0);
	writel(0x00000000, &mlc->chenh1);
	writel(0x00000000, &mlc->chenh2);
	writel(0x00000000, &mlc->chenh3); */
	writel(0x00000002, &mlc->clkenb);

	writel(0x44324030, &mlc->control0);
	//writel(0x46534030, &mlc->control0);
	writel(0x00000010, &mlc->control1);
	writel(0x00000010, &mlc->control2);
	writel(0x00000E0A, &mlc->controlt);

}

void *video_hw_init(void)
{
	GraphicDevice *pGD = &pollux_video;

	memset(pGD, 0, sizeof(GraphicDevice));
	pGD->gdfIndex = GDF_16BIT_565RGB; // GDF_16BIT_565RGB;
	pGD->gdfBytesPP = 2;
	pGD->memSize = VIDEO_MEM_SIZE;
	pGD->frameAdrs = CONFIG_SYS_SDRAM_BASE + gd->ram_size - VIDEO_MEM_SIZE;

	pGD->winSizeX = 800;
	pGD->winSizeY = 480;
	
	memset((void *)pGD->frameAdrs, 0x00, VIDEO_MEM_SIZE/4);

	init_mlc(pGD->frameAdrs);
	init_dpc();
	init_backlight();

	return pGD;
}
