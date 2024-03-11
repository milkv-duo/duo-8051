#include <stdio.h>
#include <string.h>
//#include <C8051F000.h>
#include "cvi1822.h"

#include "config.h"
#include "chip_cv1822.h"
#include "dw_ictl.h"
#include "dw_gpio.h"
#include "dw_uart.h"
#include "dw_timer.h"

#ifdef CONFIG_ENABLE_ISR

#ifdef CONFIG_DW_TIMER_ISR
extern void dw_timer1_isr(void);
#endif
void dw_ap2rtc0_isr(void);
void dw_ap2rtc1_isr(void);

void dw_ictl_intr_handler(void) __interrupt (0)
{
	uint32_t dw_ictl_status;
	dw_ictl_status = read_robot_irq(REG_DW_ICTL_FINALSTATUS_L);

	switch (dw_ictl_status) {
		case 1 << GPIO_INTR:
			//dw_gpio_isr();
			break;
#ifdef CONFIG_DW_TIMER_ISR
		case 1 << TIMER1_INTR:
			//dw_timer1_isr();
			break;
#endif
		case 1 << IRQ_AP2RTC0_INTR:
			dw_ap2rtc0_isr();
			break;
#ifdef CONFIG_IRQ_AP2RTC1
		case 1 << IRQ_AP2RTC1_INTR:
			dw_ap2rtc1_isr();
			break;
#endif
#if TEST_MAILBOX
		case 1 << MBOX_INTR:
			mailbox_isr();
			break;
#endif
#if TEST_WDT
		case 1UL << WDT_INTR:
			wdt_isr();
			break;
#endif
		default:
		break;
	}
}

#if 0
void rtc_intr_handler(void) interrupt 2 using 1
{
	xdata long rtc_ictl_status;
	rtc_ictl_status = read_robot_irq(REG_51_INT1_SRC_MASK) >> 16;
	printf("dw_ictl_intr_handler 2 --- %lx\n", rtc_ictl_status);
	dw_ictl_count++;

	printf("(REG_DW_ICTL_MASK_L) =%llx\n", mmio_read_32(REG_DW_ICTL_MASK_L));

	switch (rtc_ictl_status) {
		case 1 << TIMER1_INTR:
			dw_timer1_isr();
			break;
		case 1 << IRQ_AP2RTC0_INTR:
			dw_ap2rtc0_isr();
			break;
		case 1 << IRQ_AP2RTC1_INTR:
			dw_ap2rtc1_isr();
			break;
#if TEST_MAILBOX
		case 1 << MBOX_INTR:
			mailbox_isr();
			break;
#endif
#if TEST_WDT
		case 1UL << WDT_INTR:
			wdt_isr();
			break;
#endif
		default:
		break;
	}
}

#endif

void dw_ictl_init(void)
{
	// Mask all interrupts
	mmio_write_32(REG_DW_ICTL_MASK_L, 0xFFFFFFFF);
	mmio_write_32(REG_DW_ICTL_MASK_H, 0xFFFFFFFF);
	// Enable all interrupts
	mmio_write_32(REG_DW_ICTL_ENABLE_L, 0xFFFFFFFF);
	mmio_write_32(REG_DW_ICTL_ENABLE_H, 0xFFFFFFFF);
	// disable RTC_INT1
	mmio_write_32(REG_51_INT1_SRC_MASK, 0xffff);
}

void dw_ictl_unmask(char d)
{
	uint32_t v;
	uint32_t mask = 1UL << d;

	v = mmio_read_32(REG_DW_ICTL_MASK_L);
	v &= ~mask;
	mmio_write_32(REG_DW_ICTL_MASK_L, v);
}

void dw_ictl_mask(char d)
{
	uint32_t v;
	uint32_t mask = 1UL << d;

	v = mmio_read_32(REG_DW_ICTL_MASK_L);
	v |= mask;
	mmio_write_32(REG_DW_ICTL_MASK_L, v);
}

struct irq_action ap2rtc_action[MAX_REQUEST_NUM];
unsigned char irq_num = 0;
extern void *memset (void *s, char c, size_t n) __reentrant;

void ap2rtc_irq_init(void)
{
	irq_num = 0;
	memset((void *)ap2rtc_action, 0, sizeof(ap2rtc_action));
}
// be sure to set handler to __reentrant type
char ap2rtc_request_irq(char irqn, irq_handler_t handler, int *priv)
{
	//printf("irqn=%bu irq_num=%bu \n", irqn, irq_num );
	//printf("handler=%x\n", (int) handler);
	if (irqn > 64 || irq_num >= MAX_REQUEST_NUM)
		return -1;
	ap2rtc_action[irq_num].irqn = irqn;
	ap2rtc_action[irq_num].handler = handler;
	ap2rtc_action[irq_num].priv = priv;
	irq_num++;
	return 0;
}

char ap2rtc_unrequest_irq(char irqn)
{
	char i, j;

	for (i = 0; i < MAX_REQUEST_NUM; i++){
		for (j = 0; j < 64; j++)
			if (ap2rtc_action[i].irqn == j) {
				ap2rtc_action[i].irqn = 0xFF;
				ap2rtc_action[i].handler = NULL;
				ap2rtc_action[i].priv = 0;
				return 0;
			}
	}
	printf("can not find request_ap2rtc_irq : %d\n", irqn);
	return -1;
}

static void ap2rtc_isr_handler(unsigned char isr, unsigned long st)
{
	unsigned long status = st;
	char status_bit = 0;
	char i;

	if (isr == 1)
		status_bit += 32;
	while(status != 0) {
		if (status & 0x1) {
			for (i = 0; i < MAX_REQUEST_NUM ; i++) {
				if (ap2rtc_action[i].irqn == status_bit) {
					ap2rtc_action[i].handler(status_bit, (int*) ap2rtc_action[i].priv);
					break;
				}
			}
		}
		status_bit++;
		status >>= 1;
	};
}

void dw_ap2rtc0_isr(void)
{
	unsigned long status = 0;

	status = mmio_read_32(RTCSYS_AP2RTC_IRQ0_STATUS0);
	//printf("dw_ap2rtc0_isr status0=%lx\n", status);
	ap2rtc_isr_handler(0, status);
	status = mmio_read_32(RTCSYS_AP2RTC_IRQ0_STATUS1);
	//printf("dw_ap2rtc0_isr status1=%lx\n", status);
	ap2rtc_isr_handler(1, status);
}
#ifdef CONFIG_IRQ_AP2RTC1
void dw_ap2rtc1_isr(void)
{
	unsigned long status = 0;

	status = mmio_read_32(RTCSYS_AP2RTC_IRQ1_STATUS0);
	ap2rtc_isr_handler(0, status);
	status = mmio_read_32(RTCSYS_AP2RTC_IRQ1_STATUS1);
	ap2rtc_isr_handler(1, status);
}
#endif
void ap2rtc_irq_enable(void)
{
	mmio_write_32(RTCSYS_CTRL, 1);
	mmio_write_32(RTCSYS_IRQ, 0x30);
}

void ap2rtc_irq_disable(void)
{
	mmio_write_32(RTCSYS_CTRL, 0);
	mmio_write_32(RTCSYS_IRQ, 0);
}

char ap2rtc0_irq_unmask(unsigned char d)
{
	uint32_t v;
	dw_ictl_unmask(IRQ_AP2RTC0_INTR);
	if (d < 32) {
		v = mmio_read_32(RTCSYS_AP2RTC_IRQ0_SIGEN0);
		v |= (1UL << d);
		mmio_write_32(RTCSYS_AP2RTC_IRQ0_SIGEN0, v);
	} else if (d < 64){
		v = mmio_read_32(RTCSYS_AP2RTC_IRQ0_SIGEN1);
		v |= (1UL << (d - 32));
		mmio_write_32(RTCSYS_AP2RTC_IRQ0_SIGEN1, v);
	} else {
		printf("set wrong ap2rtc0 irq unmask : %d\n", d);
		return -1;
	}
	return 0;
}

void irq_enable(void)
{
	ap2rtc_irq_enable();
	EX0 = 1;
	EX1 = 1;
	EA = 1;
}

void irq_disable(void)
{
	ap2rtc_irq_disable();
	EX0 = 0;
	EX1 = 0;
	EA = 0;
}
#endif
