#include <stdio.h>
#include "cvi1822.h"
#include "chip_cv1822.h"
#include "dw_gpio.h"
#include "dw_uart.h"
#include "dw_ictl.h"
#include "cv_i2c.h"
#include "pwr_wdt.h"
#include "cvi_gpio.h"

void delay_us(uint8_t time)
{
	uint8_t i=0;

	while(time--) {
		i=10;
		while(i--) ;
	}
}

void reset_i2c_cmd(void)
{
	uint16_t i2c_cmd = 0xff;

	mmio_write_32(RTC_INFO1, i2c_cmd);
}

unsigned char xs1 = 0xE1;
void main(void)
{
	uint32_t i2c_cmd = 0xffffffff;
	uint32_t suspend_mode = 0x0;
	uint8_t rw = 0xff;
	uint8_t reg = 0xff;
	uint8_t value = 0xff;
	uint32_t reg_val = 0xff;
	uint32_t fsm_state = 0x0;

	//CKCON = 0x7;
	/* init dw uart*/
#ifdef CONFIG_PUTCHAR_DW_UART
	//dw_uart_init();
#endif
	// printf("cvitek mcu init2 %s\n", __TIME__);
	mmio_write_32(RTC_INFO0, 0x8051);

	/* init interrupt controller */
	dw_ictl_init();

	/* enable interrupt controller*/
	ap2rtc_irq_init();
	irq_enable();

	while(1) {

		rw = mmio_read_32(RTC_INFO1); // 0x05026020
		//printf("case1 uart test\n");
		switch (rw) {
		
		case 0x0: /* uart test */
			printf("case1 uart test\n");
			mmio_write_32(RTC_INFO1, 0xff);
			break;

		case 0x1:	/* i2c test */
		#if 1
			cv_i2c_pinmux_io_switch(1);
			reset_i2c_cmd();
			if (!cv_i2c_is_busy()) {
				delay_us(2);
				cv_i2c_master_write(0x90, 0x11);
			} else {
				mmio_write_32(RTC_INFO2, 0x66666666);
				printf("RTC_I2C is busy or corrupted\n");
			}
			mmio_write_32(RTC_INFO1, 0xff);
		#endif
			break;

		case 0x2: /* wdg test */
			pwr_wdt_start();
			mmio_write_32(RTC_INFO1, 0xff);
			break;

		case 0x3: /* wdg test */
			dw_wdt_ping();
			mmio_write_32(RTC_INFO1, 0xff);
			break;

		case 0x4: /* wdg test */
			dw_wdt_rst();
			mmio_write_32(RTC_INFO1, 0xff);
			break;

		case 0x5: /* wdg test */
			dw_wdt_rst_realease();
			mmio_write_32(RTC_INFO1, 0xff);
			break;
		
		case 0x6: /* gpio_high */
			set_gpio_direction(GPIO2_BASE,24,GPIO_DIRECTION_OUT);
			set_gpio_level(GPIO2_BASE,24,GPIO_LEVEL_HIGH);
			mmio_write_32(RTC_INFO1, 0xff);
			printf("LED_GPIO->HIGH\n");
			break;

		case 0x7: /* gpio_low */
			set_gpio_direction(GPIO2_BASE,24,GPIO_DIRECTION_OUT);
			set_gpio_level(GPIO2_BASE,24,GPIO_LEVEL_LOW);
			mmio_write_32(RTC_INFO1, 0xff);
			printf("LED_GPIO->LOW\n");
			break;

		default:
			break;
		}
	}
}
