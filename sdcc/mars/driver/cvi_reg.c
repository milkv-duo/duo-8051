#include "include/cvi_reg.h"
//#include <C8051F000.h>
#include "cvi1822.h"
#if 0
static uint16_t xdata xdata_offset_old;

void xdata_offset_set(uint16_t offset)
{
    AS_BYTES(xdata_offset_old)[1] = r51_xdata_doffset0;
    AS_BYTES(xdata_offset_old)[0] = r51_xdata_doffset1;

    r51_xdata_doffset0 = AS_BYTES(offset)[1];
    r51_xdata_doffset1 = AS_BYTES(offset)[0];
}

void xdata_offset_restore(void)
{
    r51_xdata_doffset0 = AS_BYTES(xdata_offset_old)[1];
    r51_xdata_doffset1 = AS_BYTES(xdata_offset_old)[0];
}
#endif

#ifdef __BIG_ENDIAN__
uint32_t read_robot(uint32_t addr) __reentrant
{
    uint32_t value;
	unsigned char ea;

	ea = EA;
	EA = 0;
    r51_adr0 = AS_BYTES(addr)[3];
    r51_adr1 = AS_BYTES(addr)[2];
    r51_adr2 = AS_BYTES(addr)[1];
    r51_adr3 = AS_BYTES(addr)[0];
	
    r51_we = 0 | (2 << 1);
    r51_fire = 1;

    while(r51_fire == 1)
        ;

    AS_BYTES(value)[3] = r51_rd0;
    AS_BYTES(value)[2] = r51_rd1;
    AS_BYTES(value)[1] = r51_rd2;
    AS_BYTES(value)[0] = r51_rd3;
	EA = ea;

    return value;
}

void write_robot(uint32_t addr, uint32_t value) __reentrant
{
	char ea;
    ea = EA;
	EA = 0;

    r51_adr0 = AS_BYTES(addr)[3];
    r51_adr1 = AS_BYTES(addr)[2];
    r51_adr2 = AS_BYTES(addr)[1];
    r51_adr3 = AS_BYTES(addr)[0];

    r51_wd0 = AS_BYTES(value)[3];
    r51_wd1 = AS_BYTES(value)[2];
    r51_wd2 = AS_BYTES(value)[1];
    r51_wd3 = AS_BYTES(value)[0];

    r51_we = 1 | (2 << 1);
    r51_fire = 1;

    while(r51_fire == 1)
        ;

    EA = ea;
}
#else
uint32_t read_robot(uint32_t addr) __reentrant
{
    uint32_t value;
	unsigned char ea;

	ea = EA;
	EA = 0;
    r51_adr0 = AS_BYTES(addr)[0];
    r51_adr1 = AS_BYTES(addr)[1];
    r51_adr2 = AS_BYTES(addr)[2];
    r51_adr3 = AS_BYTES(addr)[3];
	
    r51_we = 0 | (2 << 1);
    r51_fire = 1;

    while(r51_fire == 1)
        ;

    AS_BYTES(value)[0] = r51_rd0;
    AS_BYTES(value)[1] = r51_rd1;
    AS_BYTES(value)[2] = r51_rd2;
    AS_BYTES(value)[3] = r51_rd3;
		EA = ea;

    return value;
}

void write_robot(uint32_t addr, uint32_t value) __reentrant
{
	char ea;
    ea = EA;
	EA = 0;

    r51_adr0 = AS_BYTES(addr)[0];
    r51_adr1 = AS_BYTES(addr)[1];
    r51_adr2 = AS_BYTES(addr)[2];
    r51_adr3 = AS_BYTES(addr)[3];

    r51_wd0 = AS_BYTES(value)[0];
    r51_wd1 = AS_BYTES(value)[1];
    r51_wd2 = AS_BYTES(value)[2];
    r51_wd3 = AS_BYTES(value)[3];

    r51_we = 1 | (2 << 1);
    r51_fire = 1;

    while(r51_fire == 1)
        ;

    EA = ea;
}

#endif
