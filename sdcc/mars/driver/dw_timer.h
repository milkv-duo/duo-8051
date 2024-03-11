#ifndef DW_TIMER_H_WU1G9LZX
#define DW_TIMER_H_WU1G9LZX

#include "include/config.h"
#include "include/cvi_reg.h"

#define DW_TIMER_NS_PER_TICK (1000000000UL / MCU51_CLK_HZ)
#define DW_TIMER_PRELOAD_CNT 0xFFFFFFFF

#define TIMER_ID1 0x0
#define TIMER_ID2 0x1
#define TIMER_ID3 0x2
#define TIMER_ID4 0x3
#define TIMER_ID5 0x4
#define TIMER_ID6 0x5
#define TIMER_ID7 0x6
#define TIMER_ID8 0x7

#define REG_TIMERS_INTSTATUS (RTC_TIMER_BASE + 0xA0)
#define REG_TIMERS_EOI (RTC_TIMER_BASE + 0xA4)
#define REG_TIMERS_RAW_INTSTATUS (RTC_TIMER_BASE + 0xA8)
#define REG_TIMERS_COMP_VERSION (RTC_TIMER_BASE + 0xAC)
#define REG_TIMERN_LOADCNT2_BASE (RTC_TIMER_BASE + 0xB0)

#define REG_TIMER1_BASE (RTC_TIMER_BASE + 0x00)

#define REG_TIMER1_LOADCNT (REG_TIMER1_BASE)
#define REG_TIMER1_LOADCNT2 (REG_TIMERN_LOADCNT2_BASE + 0x00)
#define REG_TIMER1_CURRENT_VALUE (REG_TIMER1_BASE + 0x04)
#define REG_TIMER1_CONTROL (REG_TIMER1_BASE + 0x08)
#define REG_TIMER1_EOI (REG_TIMER1_BASE + 0x0C)
#define REG_TIMER1_INTSTATUS (REG_TIMER1_BASE + 0x10)

extern uint32_t irq_flag_timer;

void dw_timer_start(uint32_t timer_id, uint32_t cnt);
uint32_t dw_timer_stop(uint32_t timer_id);
void dw_timer_mdelay(uint32_t timer_id, uint32_t ms);
void dw_timer_sec_irq(uint32_t timer_id, uint32_t sec);

//#ifdef CONFIG_DW_TIMER_ISR
void dw_timer1_isr(void);
//#endif
int test_dw_timer();

#endif /* end of include guard: DW_TIMER_H_WU1G9LZX */
