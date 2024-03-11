#ifndef DW_ICTL_H_6B3ZKSXR
#define DW_ICTL_H_6B3ZKSXR

//#define RTC_INTR_BASE (RTC_SYS_BASE + 0x00023000)

#define REG_DW_ICTL_ENABLE_L      (RTC_INTR_BASE + 0x00)
#define REG_DW_ICTL_ENABLE_H      (RTC_INTR_BASE + 0x04)
#define REG_DW_ICTL_MASK_L        (RTC_INTR_BASE + 0x08)
#define REG_DW_ICTL_MASK_H        (RTC_INTR_BASE + 0x0c)
#define REG_DW_ICTL_FINALSTATUS_L (RTC_INTR_BASE + 0x30)
#define REG_DW_ICTL_FINALSTATUS_H (RTC_INTR_BASE + 0x34)
#define REG_DW_ICTL_BASE_OFFSET   (RTC_INTR_BASE + 0x04)

void dw_ictl_init(void);
void dw_ictl_unmask(char d);
void dw_ictl_mask(char d);
uint32_t dw_ictl_get_status();
uint32_t dw_ictl_get_count();

typedef int (*irq_handler_t) (char irqn, int *priv) __reentrant;

struct irq_action {
	irq_handler_t handler;
	int *priv;
	char irqn;
};

void dw_ictl_intr_handler(void) __interrupt 0;
char ap2rtc_request_irq(char irqn, irq_handler_t handler, int *priv);
char ap2rtc_unrequest_irq(char irqn);
char ap2rtc0_irq_unmask(unsigned char d);
void ap2rtc0_irq_enable(void);
void ap2rtc_irq_init(void);

void irq_enable(void);
void irq_disable(void);

#endif /* end of include guard: DW_ICTL_H_6B3ZKSXR */
