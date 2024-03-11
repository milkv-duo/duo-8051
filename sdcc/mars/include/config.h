#ifndef CONFIG_H_I86QB2PE

#define CONFIG_H_I86QB2PE

#define CONFIG_ENABLE_ISR
#define CONFIG_DW_TIMER_ISR
#define CONFIG_PUTCHAR_DW_UART
#define CONFIG_DW_UART_TOP
#define CONFIG_TARGET_CVITEK_CV1822
#define CONFIG_CMD_CVI_H26X_ENC

#define TEST_MAILBOX 0
#define TEST_WDT 0
#define TEST_DW_TIMER 0

#define UNUSED(x) if(x) {}

#endif /* end of include guard: CONFIG_H_I86QB2PE */
