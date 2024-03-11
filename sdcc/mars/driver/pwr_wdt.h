#ifndef PWR_WDT_H
#define PWR_WDT_H

int pwr_wdt_start(void);
int dw_wdt_ping(void);
int dw_wdt_rst(void);
int dw_wdt_rst_realease(void);

#endif