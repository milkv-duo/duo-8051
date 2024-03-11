#ifndef MAILBOX_H_MWDFTOJJ
#define MAILBOX_H_MWDFTOJJ

/*
 * // cpu0 mbox interrupt control
 * reg_cpu0_mbox_en[3:0] (0x05024000[3:0])
 * reg_cpu0_int_msk[3:0] (0x05024018[3:0])
 * reg_cpu0_int_clr[3:0] (0x05024014[3:0])
 * reg_cpu0_int_en[3:0]  (0x05024010[3:0])
 * //cpu1 mbox interrupt control
 * reg_cpu1_mbox_en[3:0] (0x05024000[19:16])
 * reg_cpu1_int_msk[3:0] (0x0502402c[3:0])
 * reg_cpu1_int_clr[3:0] (0x05024028[3:0])
 * reg_cpu1_int_en[3:0]  (0x05024024[3:0])
 * // 32 bit Information field
 * reg_sys_mailbox_mbox0[31:0] (0x05024080)
 * reg_sys_mailbox_mbox1[31:0] (0x05024084)
 * reg_sys_mailbox_mbox2[31:0] (0x05024088)
 * reg_sys_mailbox_mbox3[31:0] (0x0502408c)
 */

#define REG_CPU0_MBOX_EN (RTC_MBOX_BASE + 0x00)
#define REG_CPU0_MBOX_EN_MSB 3
#define REG_CPU0_MBOX_EN_LSB 0
#define REG_CPU0_INT_EN (RTC_MBOX_BASE + 0x10)
#define REG_CPU0_INT_EN_MSB 3
#define REG_CPU0_INT_EN_LSB 0
#define REG_CPU0_INT_CLR (RTC_MBOX_BASE + 0x14)
#define REG_CPU0_INT_CLR_MSB 3
#define REG_CPU0_INT_CLR_LSB 0
#define REG_CPU0_INT_MSK (RTC_MBOX_BASE + 0x18)
#define REG_CPU0_INT_MSK_MSB 3
#define REG_CPU0_INT_MSK_LSB 0

#define REG_CPU1_MBOX_EN (RTC_MBOX_BASE + 0x00)
#define REG_CPU1_MBOX_EN_MSB 19
#define REG_CPU1_MBOX_EN_LSB 16
#define REG_CPU1_INT_EN (RTC_MBOX_BASE + 0x24)
#define REG_CPU1_INT_EN_MSB 3
#define REG_CPU1_INT_EN_LSB 0
#define REG_CPU1_INT_MSK (RTC_MBOX_BASE + 0x2c)
#define REG_CPU1_INT_CLR_MSB 3
#define REG_CPU1_INT_CLR_LSB 0
#define REG_CPU1_INT_CLR (RTC_MBOX_BASE + 0x28)
#define REG_CPU1_INT_MSK_MSB 3
#define REG_CPU1_INT_MSK_LSB 0

#define REG_SYS_MAILBOX_MBOX0 (RTC_MBOX_BASE + 0x80)
#define REG_SYS_MAILBOX_MBOX1 (RTC_MBOX_BASE + 0x84)
#define REG_SYS_MAILBOX_MBOX2 (RTC_MBOX_BASE + 0x88)
#define REG_SYS_MAILBOX_MBOX3 (RTC_MBOX_BASE + 0x8c)

#endif /* end of include guard: MAILBOX_H_MWDFTOJJ */
