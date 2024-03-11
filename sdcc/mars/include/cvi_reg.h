#ifndef CVI_MCU51_H_ILTCKRDQ
#define CVI_MCU51_H_ILTCKRDQ

#include "config.h"
#include <stdlib.h>

typedef unsigned long uint32_t;
typedef unsigned int uint16_t;
typedef unsigned char uint8_t;

typedef signed long int32_t;
typedef signed int int16_t;
typedef signed char int8_t;

typedef unsigned long* uintptr_t;

#define mmio_write_32 write_robot
#define mmio_read_32 read_robot
#define write_robot_irq write_robot
#define read_robot_irq read_robot
#define readl read_robot
#define writel write_robot

#define mmio_write_64(addr, lval, hval)	\
		mmio_write_32(addr, lval);		\
		mmio_write_32(addr + 4, hval)

#define mmio_clrsetbits_32(addr, clear,	set)	\
		mmio_write_32(addr, (mmio_read_32(addr) & ~(clear)) | (set))

#define mmio_clrbits_32(addr, clear)	\
		mmio_write_32(addr, mmio_read_32(addr) & ~(clear))

#define mmio_setbits_32(addr, set)	\
		mmio_write_32(addr, mmio_read_32(addr) | (set));

#define AS_BYTES(x) ((uint8_t *)&(x))

#define REG_READ(NAME) get_bits_from_value(mmio_read_32(NAME##_ADDR), NAME##_MSB, NAME##_LSB)
#define REG_WRITE(NAME, value)                                                                     \
	mmio_write_32(NAME##_ADDR, modified_bits_by_value(mmio_read_32(NAME##_ADDR), value,        \
							  NAME##_MSB, NAME##_LSB)


/*
 * reg_51robot_rd [31:0]	0xE7~E4	Robot read data
 * reg_51robot_fire	0xF2	Robot fire = 1, auto set low when finish
 * reg_51robot_we	0xF3[0]	Robot write enable
 * reg_51robot_size [1:0]	0xF3[2:1]	Robot r/w size
 * reg_51robot_wd [31:0]	0xF7~F4	Robot write data
 * reg_51robot_adr [31:0]	0xFB~F8	Robot address
 * reg_51_code_banking[5:0]	0xFE[5:0]	Code banking register (for xdata)
 * reg_51xdata_doffset[15:0]	0xFD~FC	xdata data address offset (for xdata)
 */
__at (0xE4) __sfr r51_rd0;
__at (0xE5) __sfr r51_rd1;
__at (0xE6) __sfr r51_rd2;
__at (0xE7) __sfr r51_rd3;

__at (0xF2) __sfr r51_fire;
__at (0xF3) __sfr r51_we;

__at (0xF4) __sfr r51_wd0;
__at (0xF5) __sfr r51_wd1;
__at (0xF6) __sfr r51_wd2;
__at (0xF7) __sfr r51_wd3;

__at (0xF8) __sfr r51_adr0;
__at (0xF9) __sfr r51_adr1;
__at (0xFA) __sfr r51_adr2;
__at (0xFB) __sfr r51_adr3;

__at (0xF7) __sfr r51_code_banking;

__at (0xFC) __sfr r51_xdata_doffset0;
__at (0xFD) __sfr r51_xdata_doffset1;

/*
 *
 */

uint32_t read_robot(uint32_t addr) __reentrant;
void write_robot(uint32_t addr, uint32_t value) __reentrant;
uint32_t vdiRead(uint32_t pVenc, uint32_t addr);
void vdiWrite(uint32_t pVenc, uint32_t addr, uint32_t data);

#endif /* end of include guard: CVI_MCU51_H_ILTCKRDQ */
