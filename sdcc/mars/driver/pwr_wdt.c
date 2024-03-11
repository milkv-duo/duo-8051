#include"pwr_wdt.h"
#include "cvi_reg.h"

#define WDOG_CONTROL_REG_OFFSET		    0x00
#define WDOG_CONTROL_REG_WDT_EN_MASK	    0x01
#define WDOG_CONTROL_REG_RESP_MODE_MASK	    0x02
#define WDOG_TIMEOUT_RANGE_REG_OFFSET	    0x04
#define WDOG_TIMEOUT_RANGE_TOPINIT_SHIFT    4
#define WDOG_CURRENT_COUNT_REG_OFFSET	    0x08
#define WDOG_COUNTER_RESTART_REG_OFFSET     0x0c
#define WDOG_COUNTER_RESTART_KICK_VALUE	    0x76


#define pwr_wdt_base 0x0502D000

static void dw_wdt_arm_system_reset(void)
{
	uint32_t val = mmio_read_32(pwr_wdt_base + WDOG_CONTROL_REG_OFFSET);

	/* Disable interrupt mode; always perform system reset. */
	val &= ~WDOG_CONTROL_REG_RESP_MODE_MASK;
	/* Enable watchdog. */
	val |= WDOG_CONTROL_REG_WDT_EN_MASK;
	mmio_write_32(pwr_wdt_base + WDOG_CONTROL_REG_OFFSET, val);

}

int pwr_wdt_start(void)
{
    mmio_write_32(0x050260E0, 0x01);// enable watch dog req rst
	mmio_write_32(0x050250A0, 0x01);//wdt ctrl, enable wdt triger warm reset
 	mmio_write_32(pwr_wdt_base + 0x4, 0x22); // WDT_TORR ，time=((1<<(top+16)) /32768) rtc watch dog counter clk is 32k
    dw_wdt_arm_system_reset();
	return 0;
}

int dw_wdt_ping(void)
{

	mmio_write_32(pwr_wdt_base +
	       WDOG_COUNTER_RESTART_REG_OFFSET, WDOG_COUNTER_RESTART_KICK_VALUE);

	return 0;
}

int dw_wdt_rst(void)
{
    uint32_t val = mmio_read_32(0x5025018);
	mmio_write_32(0x5025018, 0xfffbffff & val);
	return 0;
}

int dw_wdt_rst_realease(void)
{
    uint32_t val = mmio_read_32(0x5025018);
	mmio_write_32(0x5025018, 0x40000 | val);
	return 0;
}