/*
 * Renesas MX-G (R8A03022BG) Setup
 *
 *  Copyright (C) 2008, 2009  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/serial_sci.h>
#include <linux/sh_timer.h>

enum {
	UNUSED = 0,

	/* interrupt sources */
	IRQ0, IRQ1, IRQ2, IRQ3, IRQ4, IRQ5, IRQ6, IRQ7,
	IRQ8, IRQ9, IRQ10, IRQ11, IRQ12, IRQ13, IRQ14, IRQ15,

	PINT0, PINT1, PINT2, PINT3, PINT4, PINT5, PINT6, PINT7,
	SINT8, SINT7, SINT6, SINT5, SINT4, SINT3, SINT2, SINT1,

	SCIF0, SCIF1,

	MTU2_GROUP1, MTU2_GROUP2, MTU2_GROUP3, MTU2_GROUP4, MTU2_GROUP5,
	MTU2_TGI3B, MTU2_TGI3C,

	/* interrupt groups */
	PINT,
};

static struct intc_vect vectors[] __initdata = {
	INTC_IRQ(IRQ0, 64), INTC_IRQ(IRQ1, 65),
	INTC_IRQ(IRQ2, 66), INTC_IRQ(IRQ3, 67),
	INTC_IRQ(IRQ4, 68), INTC_IRQ(IRQ5, 69),
	INTC_IRQ(IRQ6, 70), INTC_IRQ(IRQ7, 71),
	INTC_IRQ(IRQ8, 72), INTC_IRQ(IRQ9, 73),
	INTC_IRQ(IRQ10, 74), INTC_IRQ(IRQ11, 75),
	INTC_IRQ(IRQ12, 76), INTC_IRQ(IRQ13, 77),
	INTC_IRQ(IRQ14, 78), INTC_IRQ(IRQ15, 79),

	INTC_IRQ(PINT0, 80), INTC_IRQ(PINT1, 81),
	INTC_IRQ(PINT2, 82), INTC_IRQ(PINT3, 83),
	INTC_IRQ(PINT4, 84), INTC_IRQ(PINT5, 85),
	INTC_IRQ(PINT6, 86), INTC_IRQ(PINT7, 87),

	INTC_IRQ(SINT8, 94), INTC_IRQ(SINT7, 95),
	INTC_IRQ(SINT6, 96), INTC_IRQ(SINT5, 97),
	INTC_IRQ(SINT4, 98), INTC_IRQ(SINT3, 99),
	INTC_IRQ(SINT2, 100), INTC_IRQ(SINT1, 101),

	INTC_IRQ(SCIF0, 220), INTC_IRQ(SCIF0, 221),
	INTC_IRQ(SCIF0, 222), INTC_IRQ(SCIF0, 223),
	INTC_IRQ(SCIF1, 224), INTC_IRQ(SCIF1, 225),
	INTC_IRQ(SCIF1, 226), INTC_IRQ(SCIF1, 227),

	INTC_IRQ(MTU2_GROUP1, 228), INTC_IRQ(MTU2_GROUP1, 229),
	INTC_IRQ(MTU2_GROUP1, 230), INTC_IRQ(MTU2_GROUP1, 231),
	INTC_IRQ(MTU2_GROUP1, 232), INTC_IRQ(MTU2_GROUP1, 233),

	INTC_IRQ(MTU2_GROUP2, 234), INTC_IRQ(MTU2_GROUP2, 235),
	INTC_IRQ(MTU2_GROUP2, 236), INTC_IRQ(MTU2_GROUP2, 237),
	INTC_IRQ(MTU2_GROUP2, 238), INTC_IRQ(MTU2_GROUP2, 239),

	INTC_IRQ(MTU2_GROUP3, 240), INTC_IRQ(MTU2_GROUP3, 241),
	INTC_IRQ(MTU2_GROUP3, 242), INTC_IRQ(MTU2_GROUP3, 243),

	INTC_IRQ(MTU2_TGI3B, 244),
	INTC_IRQ(MTU2_TGI3C, 245),

	INTC_IRQ(MTU2_GROUP4, 246), INTC_IRQ(MTU2_GROUP4, 247),
	INTC_IRQ(MTU2_GROUP4, 248), INTC_IRQ(MTU2_GROUP4, 249),
	INTC_IRQ(MTU2_GROUP4, 250), INTC_IRQ(MTU2_GROUP4, 251),

	INTC_IRQ(MTU2_GROUP5, 252), INTC_IRQ(MTU2_GROUP5, 253),
	INTC_IRQ(MTU2_GROUP5, 254), INTC_IRQ(MTU2_GROUP5, 255),
};

static struct intc_group groups[] __initdata = {
	INTC_GROUP(PINT, PINT0, PINT1, PINT2, PINT3,
		   PINT4, PINT5, PINT6, PINT7),
};

static struct intc_prio_reg prio_registers[] __initdata = {
	{ 0xfffd9418, 0, 16, 4, /* IPR01 */ { IRQ0, IRQ1, IRQ2, IRQ3 } },
	{ 0xfffd941a, 0, 16, 4, /* IPR02 */ { IRQ4, IRQ5, IRQ6, IRQ7 } },
	{ 0xfffd941c, 0, 16, 4, /* IPR03 */ { IRQ8, IRQ9, IRQ10, IRQ11 } },
	{ 0xfffd941e, 0, 16, 4, /* IPR04 */ { IRQ12, IRQ13, IRQ14, IRQ15 } },
	{ 0xfffd9420, 0, 16, 4, /* IPR05 */ { PINT, 0, 0, 0 } },
	{ 0xfffd9800, 0, 16, 4, /* IPR06 */ { } },
	{ 0xfffd9802, 0, 16, 4, /* IPR07 */ { } },
	{ 0xfffd9804, 0, 16, 4, /* IPR08 */ { } },
	{ 0xfffd9806, 0, 16, 4, /* IPR09 */ { } },
	{ 0xfffd9808, 0, 16, 4, /* IPR10 */ { } },
	{ 0xfffd980a, 0, 16, 4, /* IPR11 */ { } },
	{ 0xfffd980c, 0, 16, 4, /* IPR12 */ { } },
	{ 0xfffd980e, 0, 16, 4, /* IPR13 */ { } },
	{ 0xfffd9810, 0, 16, 4, /* IPR14 */ { 0, 0, 0, SCIF0 } },
	{ 0xfffd9812, 0, 16, 4, /* IPR15 */
		{ SCIF1, MTU2_GROUP1, MTU2_GROUP2, MTU2_GROUP3 } },
	{ 0xfffd9814, 0, 16, 4, /* IPR16 */
		{ MTU2_TGI3B, MTU2_TGI3C, MTU2_GROUP4, MTU2_GROUP5 } },
};

static struct intc_mask_reg mask_registers[] __initdata = {
	{ 0xfffd9408, 0, 16, /* PINTER */
	  { 0, 0, 0, 0, 0, 0, 0, 0,
	    PINT7, PINT6, PINT5, PINT4, PINT3, PINT2, PINT1, PINT0 } },
};

static DECLARE_INTC_DESC(intc_desc, "mxg", vectors, groups,
			 mask_registers, prio_registers, NULL);

static struct sh_timer_config mtu2_0_platform_data = {
	.name = "MTU2_0",
	.channel_offset = -0x80,
	.timer_bit = 0,
	.clk = "peripheral_clk",
	.clockevent_rating = 200,
};

static struct resource mtu2_0_resources[] = {
	[0] = {
		.name	= "MTU2_0",
		.start	= 0xff801300,
		.end	= 0xff801326,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= 228,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_device mtu2_0_device = {
	.name		= "sh_mtu2",
	.id		= 0,
	.dev = {
		.platform_data	= &mtu2_0_platform_data,
	},
	.resource	= mtu2_0_resources,
	.num_resources	= ARRAY_SIZE(mtu2_0_resources),
};

static struct sh_timer_config mtu2_1_platform_data = {
	.name = "MTU2_1",
	.channel_offset = -0x100,
	.timer_bit = 1,
	.clk = "peripheral_clk",
	.clockevent_rating = 200,
};

static struct resource mtu2_1_resources[] = {
	[0] = {
		.name	= "MTU2_1",
		.start	= 0xff801380,
		.end	= 0xff801390,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= 234,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_device mtu2_1_device = {
	.name		= "sh_mtu2",
	.id		= 1,
	.dev = {
		.platform_data	= &mtu2_1_platform_data,
	},
	.resource	= mtu2_1_resources,
	.num_resources	= ARRAY_SIZE(mtu2_1_resources),
};

static struct sh_timer_config mtu2_2_platform_data = {
	.name = "MTU2_2",
	.channel_offset = 0x80,
	.timer_bit = 2,
	.clk = "peripheral_clk",
	.clockevent_rating = 200,
};

static struct resource mtu2_2_resources[] = {
	[0] = {
		.name	= "MTU2_2",
		.start	= 0xff801000,
		.end	= 0xff80100a,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= 240,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_device mtu2_2_device = {
	.name		= "sh_mtu2",
	.id		= 2,
	.dev = {
		.platform_data	= &mtu2_2_platform_data,
	},
	.resource	= mtu2_2_resources,
	.num_resources	= ARRAY_SIZE(mtu2_2_resources),
};

static struct plat_sci_port sci_platform_data[] = {
	{
		.mapbase	= 0xff804000,
		.flags		= UPF_BOOT_AUTOCONF,
		.type		= PORT_SCIF,
		.irqs		= { 220, 220, 220, 220 },
	}, {
		.flags = 0,
	}
};

static struct platform_device sci_device = {
	.name		= "sh-sci",
	.id		= -1,
	.dev		= {
		.platform_data	= sci_platform_data,
	},
};

static struct platform_device *mxg_devices[] __initdata = {
	&sci_device,
	&mtu2_0_device,
	&mtu2_1_device,
	&mtu2_2_device,
};

static int __init mxg_devices_setup(void)
{
	return platform_add_devices(mxg_devices,
				    ARRAY_SIZE(mxg_devices));
}
__initcall(mxg_devices_setup);

void __init plat_irq_setup(void)
{
	register_intc_controller(&intc_desc);
}

static struct platform_device *mxg_early_devices[] __initdata = {
	&mtu2_0_device,
	&mtu2_1_device,
	&mtu2_2_device,
};

void __init plat_early_device_setup(void)
{
	early_platform_add_devices(mxg_early_devices,
				   ARRAY_SIZE(mxg_early_devices));
}