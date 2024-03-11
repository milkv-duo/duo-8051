#include "config.h"
#include "cvi_reg.h"
#include "chip_cv1822.h"
#include "dw_uart.h"

#ifdef CONFIG_DW_UART_RTC
#define uart_base RTC_UART_BASE
#endif

#ifdef CONFIG_DW_UART_TOP
#define uart_base UART0_BASE
#endif

#ifdef CONFIG_PUTCHAR_DW_UART
char putchar (char c)
{
	if (c == '\n')
		dw_uart_putc('\r');
	return dw_uart_putc(c);
}
#endif /* CONFIG_PUTCHAR_DW_UART */


#ifdef uart_base

char dw_uart_init(void)
{
	unsigned int divisor;

	//mmio_write_32(TOP_BASE + 0x1000 + 0x90, 2); // PWR_WAKEUP0 PWR_UART0_TX 2
	//mmio_write_32(TOP_BASE + 0x1000 + 0xA4, 2); // PWR_GPIO0 PWR_UART0_RX 2

	divisor = MCU51_CLK_HZ / (16 * 115200);
	mmio_write_32(uart_base + UARTMCR, 0x10); /* LOOP */

	mmio_write_32(uart_base + UARTLCR, UARTLCR_DLAB);
	mmio_write_32(uart_base + UARTDLL, divisor & 0xff);
	mmio_write_32(uart_base + UARTDLLM, (divisor >> 8) & 0xff);
	mmio_write_32(uart_base + UARTLCR, UARTLCR_WORDSZ_8);

	mmio_write_32(uart_base + UARTIER, 0x0); /* no interrupt */
	mmio_write_32(uart_base + UARTFCR, UARTFCR_FIFOEN | UARTFCR_TXCLR | UARTFCR_RXCLR);
	mmio_write_32(uart_base + UARTMCR, 0x3); /* DTR + RTS */

	return 0;
}

char dw_uart_putc(char c)
{
	while ((mmio_read_32(uart_base + UARTLSR) & (UARTLSR_TEMT | UARTLSR_THRE)) !=
	       (UARTLSR_TEMT | UARTLSR_THRE))
		;

	mmio_write_32(uart_base + UARTTX, c);
	mmio_write_32(RTC_INFO3, 0x12312313);
	return c;
}
#endif

#if 0
char dw_uart_getc(void)
{
	while ((mmio_read_32(uart_base + UARTLSR) & UARTLSR_RDR) == 0)
		;

	return mmio_read_32(uart_base + UARTRX);
}
#endif
#if 0
char dw_uart_putc_irq(char c)
{
	while ((read_robot_irq(uart_base + UARTLSR) & (UARTLSR_TEMT | UARTLSR_THRE)) !=
	       (UARTLSR_TEMT | UARTLSR_THRE))
		;

	write_robot_irq(uart_base + UARTTX, c);

	return c;
}

#endif
