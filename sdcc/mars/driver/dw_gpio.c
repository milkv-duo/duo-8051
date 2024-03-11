#include <stdio.h>
#include "cvi_reg.h"
#include "chip_cv1822.h"
#include "dw_ictl.h"
#include "dw_gpio.h"
#include "dw_gpio.h"

uint32_t irq_flag_gpio = 0;

void dw_gpio_isr(void)
{
	read_robot_irq(REG_GPIO_EOI);
	irq_flag_gpio = read_robot_irq(REG_GPIO_INTSTATUS);
	dw_ictl_mask(GPIO_INTR);

	// mmio_write_32(RTC_INFO2, irq_flag_gpio);
}
