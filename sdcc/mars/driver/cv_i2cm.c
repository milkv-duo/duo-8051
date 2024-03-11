/*
 * Copyright (c) 2019, Cvitek. All rights reserved.
 *
 */

#include "cvi_reg.h"
#include "chip_cv1822.h"
#include "cv_i2c.h"
#include <stdio.h>

#define I2C_WRITEL(reg, val) mmio_write_32(0x0502b000 + reg, val)
#define I2C_READL(reg) mmio_read_32(0x0502b000 + reg)
#define MAX_RETRY 2000

uint32_t i2c_scl_latch;
uint32_t i2c_sda_latch;
uint32_t i2c_scl_pinmux;
uint32_t i2c_sda_pinmux;
uint32_t i2c_scl_io;
uint32_t i2c_sda_io;

uint8_t cv_i2c_is_busy(void)
{
	uint32_t try_cnt = MAX_RETRY;

	while (try_cnt) {
		uint32_t irq1 = I2C_READL(REG_I2C_RAW_INT_STAT);

		if (irq1 & BIT_I2C_INT_TX_EMPTY) {
			return 0;
		}
		try_cnt--;
	}

	return 1;
}
//
//  cv_i2c_master_write(unsigned short reg, uint8_t value)
//		reg: 16-bits register address
//		data: 8-bits data
//
void cv_i2c_master_write(unsigned short reg, uint8_t value) __reentrant
{
	// 1. send reg addr - send MSB first customized for sensor
	I2C_WRITEL(REG_I2C_DATA_CMD, reg | BIT_I2C_CMD_DATA_RESTART_BIT);
	// 2. send data
	I2C_WRITEL(REG_I2C_DATA_CMD, value | BIT_I2C_CMD_DATA_STOP_BIT);
}

//
//  cv_i2c_master_read(unsigned short reg)
//		reg: 16-bits register address
//		return 8-bits data
//
uint8_t cv_i2c_master_read(uint8_t reg) __reentrant
{
	uint16_t value1 = 0x0f;
	uint32_t try_cnt = MAX_RETRY;
	// 1. send reg addr - send MSB first customized for sensor
	//I2C_WRITEL(REG_I2C_DATA_CMD, reg | BIT_I2C_CMD_DATA_RESTART_BIT );
	I2C_WRITEL(REG_I2C_DATA_CMD, reg);
	// 2. send read cmd
	I2C_WRITEL(REG_I2C_DATA_CMD, 0 |
		BIT_I2C_CMD_DATA_READ_BIT |
		BIT_I2C_CMD_DATA_STOP_BIT);
	while (try_cnt) {
		uint32_t irq1 = I2C_READL(REG_I2C_RAW_INT_STAT);

		if (irq1 & BIT_I2C_INT_RX_FULL) {
			value1 = I2C_READL(REG_I2C_DATA_CMD);
			break;
		}
		try_cnt--;
	}

	return value1;
}

void cv_i2c_pinmux_io_switch(uint8_t turn_on)
{
	if (turn_on == 0) {
	/* siwtch back to gpio mode */
		mmio_write_32(0x50270A8, i2c_scl_latch);
		mmio_write_32(0x50270AC, i2c_sda_latch);
		//mmio_write_32(0x030010A8, i2c_scl_pinmux);
		//mmio_write_32(0x030010AC, i2c_sda_pinmux);
		//mmio_write_32(0x05027030, i2c_scl_io);
		//mmio_write_32(0x05027034, i2c_sda_io);
	} else {
	/* switch to RTC I2C pinmux and io pad setting */
		i2c_scl_latch = mmio_read_32(0x50270A8);
		i2c_sda_latch = mmio_read_32(0x50270AC);
		mmio_write_32(0x50270A8, 0x464);
		mmio_write_32(0x50270AC, 0x4644);
		//mmio_write_32(0x030010A8, 0x5);
		//mmio_write_32(0x030010AC, 0x5);
		//mmio_write_32(0x05027030, 0x44);
		//mmio_write_32(0x05027034, 0x44);
//		mmio_write_32(RTC_INFO2, mmio_read_32(0x50270A8));
//		mmio_write_32(RTC_INFO3, mmio_read_32(0x50270AC));
	}
}
//
//  cv_i2c_master_init(unsigned short addr , unsigned short speed)
//		addr: slave address
//		speed: I2C_400KHZ/I2C_100KHZ - i2c_speed
//		return none
//
void cv_i2c_master_init(unsigned short addr, unsigned short speed) __reentrant
{
	unsigned int value1 = 0;
	unsigned int value2 = 0;

	i2c_scl_pinmux = mmio_read_32(0x030010A8);
	i2c_sda_pinmux = mmio_read_32(0x030010AC);
	i2c_scl_io = mmio_read_32(0x05027030);
	i2c_sda_io = mmio_read_32(0x05027034);

	I2C_WRITEL(REG_I2C_ENABLE, 0);

	if (speed == I2C_400KHZ) {
		I2C_WRITEL(REG_I2C_CON, 0x65);
	} else {	// default is 100KHz
		I2C_WRITEL(REG_I2C_CON, 0x63);
	}

	I2C_WRITEL(REG_I2C_TAR, addr);

	value1 = I2C_READL(REG_I2C_TAR);
	value2 = I2C_READL(REG_I2C_CON);

	I2C_WRITEL(REG_I2C_SS_SCL_HCNT, 0x1A4);
	I2C_WRITEL(REG_I2C_SS_SCL_LCNT, 0x1F0);
	I2C_WRITEL(REG_I2C_FS_SCL_HCNT, 27);
	I2C_WRITEL(REG_I2C_FS_SCL_LCNT, 45);

	I2C_WRITEL(REG_I2C_INT_MASK, 0x00);

	I2C_WRITEL(REG_I2C_RX_TL,  0x00);
	I2C_WRITEL(REG_I2C_TX_TL,  0x01);
	I2C_WRITEL(REG_I2C_SDA_HOLD,  0x1E);

	I2C_WRITEL(REG_I2C_ENABLE, 1);

	I2C_READL(REG_I2C_CLR_INTR);
}
