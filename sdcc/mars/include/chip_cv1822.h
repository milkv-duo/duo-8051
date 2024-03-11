#ifndef CV1822_REGS_H_V3YENMU2
#define CV1822_REGS_H_V3YENMU2

#include "config.h"
#include "cvi_reg.h"

#define MCU51_CLK_HZ 25000000

#define GPIO_IN 0x0
#define GPIO_OUT 0x1

/*
 * TOP
 */
#define TOP_BASE 0x03000000
#define REG_GP_REG0 (TOP_BASE + 0x80)
#define REG_GP_REG1 (TOP_BASE + 0x84)

/*
 * PERI
 */
#define HSPERI_BASE 0x04000000
#define UART0_BASE (HSPERI_BASE + 0x00140000)
#define UART1_BASE (HSPERI_BASE + 0x00150000)
#define UART2_BASE (HSPERI_BASE + 0x00160000)
#define UART3_BASE (HSPERI_BASE + 0x00170000)
#define UART4_BASE (HSPERI_BASE + 0x001C0000)

/*
 * RTC
 */
#define RTC_SYS_BASE 0x05000000

#define RTC_SRAM_BASE 0x05200000
#define RTC_SRAM_SIZE 0x2000 // 8KB

#define RTC_SPINOR_BASE 0x05400000
#define RTC_SPINOR_SIZE 0x400000 // 4MB

#define RTC_TIMER_BASE (RTC_SYS_BASE + 0x00020000)
#define RTC_GPIO_BASE  (RTC_SYS_BASE + 0x00021000)
#define RTC_UART_BASE  (RTC_SYS_BASE + 0x00022000)
#define RTC_INTR_BASE  (RTC_SYS_BASE + 0x00023000)
#define RTC_MBOX_BASE  (RTC_SYS_BASE + 0x00024000)
#define RTC_CTRL_BASE  (RTC_SYS_BASE + 0x00025000)
#define RTC_BASE       (RTC_SYS_BASE + 0x00026000)
#define RTC_IOCTRL     (RTC_SYS_BASE + 0x00027000)
#define RTC_SEC_BASE   (RTC_SYS_BASE + 0x00029000)
#define RTC_I2C_BASE   (RTC_SYS_BASE + 0x0002B000)
#define RTC_SAR_BASE   (RTC_SYS_BASE + 0x0002C000)
#define RTC_WDT_BASE   (RTC_SYS_BASE + 0x0002D000)

#define REG_51_INT1_SRC_MASK (RTC_CTRL_BASE + 0x07C)

#define REG_RTC_CTRL0 (RTC_CTRL_BASE + 0x8)
#define REG_RTC_CTRL_STATUS0 (RTC_CTRL_BASE + 0xC)

#define RTC_INFO0 (RTC_BASE + 0x1C)	// mcu state
#define RTC_INFO1 (RTC_BASE + 0x20)	// mcu run state
#define RTC_INFO2 (RTC_BASE + 0x24)	//
#define RTC_INFO3 (RTC_BASE + 0x28)	//

#define CTRL_SELPHY_PWR_BUTTON1 0x84

#define RTC_FSM_STATE (RTC_BASE + 0xD4)

#define ST_OFF           0x0
#define ST_UP            0x1
#define ST_DN            0x2
#define ST_ON            0x3
#define ST_PWR_CYC2      0x4
#define ST_PWR_CYC       0x6
#define ST_WARM_RESET    0x7
#define ST_IDEL          0x8
#define ST_SUSP          0x9
#define ST_PRE_SUSP      0xB

/*
 * Interrupt number
 */
#define WDT_INTR         15UL
#define SARADC_INTR      14UL
#define HW_THM_SHDN_INTR 13UL
#define ST_CHANGE_INTR   12UL
#define I2C_INTR         11UL
#define IRQ_AP2RTC1_INTR 10UL
#define IRQ_AP2RTC0_INTR 9UL
#define TIMER0_INTR      8UL
#define TIMER1_INTR      7UL
#define SPINOR1_INTR     6UL
#define UART_INTR        5UL
#define GPIO_INTR        4UL
#define SD1_WAKEUP_INTR  3UL
#define SD1_INTR         2UL
#define MBOX_INTR        1UL
#define VBAT_DET_INTR    0UL

/*
 * AP2RTC configuraiton
 */
#define RTCSYS_CTRL                  (TOP_BASE + 0x248)
#define RTCSYS_IRQ                   (TOP_BASE + 0x24C)
#define RTCSYS_AP2RTC_IRQ0_SIGEN0    (TOP_BASE + 0x250)
#define RTCSYS_AP2RTC_IRQ0_SIGEN1    (TOP_BASE + 0x254)
#define RTCSYS_AP2RTC_IRQ0_STATUS0   (TOP_BASE + 0x258)
#define RTCSYS_AP2RTC_IRQ0_STATUS1   (TOP_BASE + 0x25C)
#define RTCSYS_AP2RTC_IRQ1_SIGEN0    (TOP_BASE + 0x260)
#define RTCSYS_AP2RTC_IRQ1_SIGEN1    (TOP_BASE + 0x264)
#define RTCSYS_AP2RTC_IRQ1_STATUS0   (TOP_BASE + 0x268)
#define RTCSYS_AP2RTC_IRQ1_STATUS1   (TOP_BASE + 0x26C)

/*
 * Limit irq_isr callback func number to 4
 */
#define MAX_REQUEST_NUM    4
#define MAX_AP2RTC_IRQ    64

/*
 * AP2RTC_IRQ configuration
 */
#define H264C_INTR         25
#define H265C_INTR         26
#define VIP_INT_ISP_TOP    48
#define VIP_INT_SC_TOP     49
#define VIP_INT_CSI_MAC0   50
#define VIP_INT_CSI_MAC1   51

/*
 * DMA
 */
#define SYSDMA_BASE		(HSPERI_BASE + 0x00330000)

/*
 * I2C
 */
#define I2C0_BASE		(HSPERI_BASE + 0x00000000)
#define I2C1_BASE		(HSPERI_BASE + 0x00010000)
#define I2C2_BASE		(HSPERI_BASE + 0x00020000)
#define I2C3_BASE		(HSPERI_BASE + 0x00030000)

/*
 * SRAM base address
 */
#define RTC_SRAM_BASE   0x05200000
#define TPU_SRAM_BASE   0x0c020000

#endif /* end of include guard: CV1822_REGS_H_V3YENMU2 */
