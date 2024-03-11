#ifndef __DW_GPIO_H__
#define __DW_GPIO_H__


#define REG_GPIO_INTEN (RTC_GPIO_BASE + 0x30)
#define REG_GPIO_INT_MASK (RTC_GPIO_BASE + 0x34)
#define REG_GPIO_INT_TYPE (RTC_GPIO_BASE + 0x38)
#define REG_GPIO_INT_POLARITY (RTC_GPIO_BASE + 0x3C)
#define REG_GPIO_INTSTATUS (RTC_GPIO_BASE + 0x40)
#define REG_GPIO_EOI (RTC_GPIO_BASE + 0x4C)
#define REG_GPIO_READ (RTC_GPIO_BASE + 0x50)

#define BIT(x) ((uint32_t)1 << x)

#define GPIO_SW_L				BIT(0)
#define GPIO_KEY_MENU			BIT(6)
#define GPIO_SW_R				BIT(7)
#define GPIO_GSENSOR_INT1		BIT(5)
#define GPIO_PMIC_IRQ			BIT(8)
#define GPIO_PMIC_PWROK			BIT(12)
#define GPIO_GSENSOR_INT2		BIT(13)

extern uint32_t irq_flag_gpio;

void dw_gpio_isr(void);

void dw_gpio_set_isr_failling(uint8_t pin);

#endif
