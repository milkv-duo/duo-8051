#include <stdio.h>
//#include <REG51.H>
#include "cvi_reg.h"
#include "chip_cv1822.h"
#include "dw_timer.h"
#include "dw_ictl.h"
#include "dw_uart.h"

// static uint32_t timer_loaded_cnt;
uint32_t irq_flag_timer = 0;

static uint16_t cnt_more_128sec = 0;

void dw_timer_mdelay(uint32_t timer_id, uint32_t ms)
{
	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x0);
	mmio_write_32(REG_TIMER1_LOADCNT + timer_id * 0x14, ms * 25000);
	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x3);

	while(!mmio_read_32(REG_TIMER1_INTSTATUS + timer_id * 0x14))
		;
}

void dw_timer_sec_irq(uint32_t timer_id, uint32_t sec)
{
	uint32_t ms;

	irq_flag_timer = cnt_more_128sec = 0;

	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x0);

	if (sec == 0)
	{
		dw_ictl_mask(TIMER1_INTR);
		return;
	}

	if (sec >= 128)	// more than 128 sec
	{
		cnt_more_128sec = sec >> 7;
		sec = sec & ((1 << 7) - 1);
	}

	ms = sec*1000;

	mmio_write_32(REG_TIMER1_LOADCNT + timer_id * 0x14, ms * 25000);
	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x3);

	dw_ictl_unmask(TIMER1_INTR);
}

#if 0
void dw_timer_start(uint32_t timer_id, uint32_t cnt)
{
	timer_loaded_cnt = cnt;
	printf("timer_loaded_cnt=%lu\n", timer_loaded_cnt);

	// disable timer
	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x0);
	// set timer load count
	mmio_write_32(REG_TIMER1_LOADCNT + timer_id * 0x14, timer_loaded_cnt);
	// enable timer
	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x3);
}

uint32_t dw_timer_stop(uint32_t timer_id)
{
	uint32_t time_end;
	uint32_t timer_interval_ms;

	time_end = mmio_read_32(REG_TIMER1_CURRENT_VALUE + timer_id * 0x14);

	// disable timer
	mmio_write_32(REG_TIMER1_CONTROL + timer_id * 0x14, 0x0);

	timer_interval_ms = (timer_loaded_cnt - time_end) * DW_TIMER_NS_PER_TICK / 1000000;

	return timer_interval_ms;
}
#endif

#ifdef CONFIG_DW_TIMER_ISR
// static int dw_timer_tick;
// static uint32_t dw_timer_eoi;

void dw_timer1_isr(void)
{
	read_robot_irq(REG_TIMER1_EOI);
	// dw_timer_tick++;

	if (cnt_more_128sec--)
	{
		mmio_write_32(REG_TIMER1_CONTROL, 0x0);
		mmio_write_32(REG_TIMER1_LOADCNT, ((uint32_t)128 * 1000) * 25000);
		mmio_write_32(REG_TIMER1_CONTROL, 0x3);

		return;
	}

	irq_flag_timer = 1;

	dw_ictl_mask(TIMER1_INTR);

}
#endif

#if TEST_DW_TIMER
static int count;
static int dw_timer_tick_int1;

int test_dw_timer()
{
	int nsec = 5;

	EA = 0;

	printf("test_dw_timer() T2:\n");

	dw_timer_tick = 0;
	dw_timer_tick_int1 = 0;

	dw_timer_start(TIMER_ID1, MCU51_CLK_HZ * nsec);
	//dw_timer_start(TIMER_ID1, 32L * 1024L * nsec);
	printf("REG_TIMER1_LOADCNT: 0x%08lx nsec=%d\n", read_robot(REG_TIMER1_LOADCNT), nsec);

	// Enable dw_timer interrupt
	dw_ictl_unmask(TIMER1_INTR);

	// Unmask int1
	//write_robot(REG_51_INT1_SRC_MASK, 0xff7f);
	//printf("REG_51_INT1_SRC_MASK: 0x%08lx\n", read_robot(REG_51_INT1_SRC_MASK));

	EX0 = 1;
	EX1 = 1;
	EA = 1;


#if 1
	//printf("wait dw_timer_tick.\n");
	while(dw_timer_tick < 10)
		;
	printf("dw_timer_tick =%d\n", dw_timer_tick);
#else
	printf("dw_timer_tick=%u dw_timer_tick_int1=%u\n", dw_timer_tick, dw_timer_tick_int1);
	puts("wait dw_timer_tick_int1..\n");
	while (dw_timer_tick_int1 == 0) {
		// printf("T: count=%d %lu %u\n", count, dw_timer_tick, dw_timer_tick_int1);
		// printf("REG_51_INT1_SRC_MASK: 0x%08lx\n", read_robot(REG_51_INT1_SRC_MASK));
	}
#endif
#if 0
	printf("T: %u %u 0x%lx\n", dw_timer_tick, dw_timer_tick_int1, read_robot(REG_51_INT1_SRC_MASK));
	printf("REG_TIMERS_INTSTATUS: 0x%08lx\n", read_robot(REG_TIMERS_INTSTATUS));
	printf("REG_TIMERS_RAW_INTSTATUS: 0x%08lx\n", read_robot(REG_TIMERS_RAW_INTSTATUS));

	xs1 = 0xB7;
#endif
	return 0;
}

#endif
