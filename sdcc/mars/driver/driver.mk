DRV_PATH = $(BUILDDIR)/../../driver

#put the critical source code in rtc_sram by files oder, do not change the order of c_srcs
c_srcs += \
	$(DRV_PATH)/cvi_reg.c \
	$(DRV_PATH)/dw_ictl.c \
	$(DRV_PATH)/cv_i2cm.c \
	$(DRV_PATH)/dw_gpio.c \
	$(DRV_PATH)/dw_uart.c \
	$(DRV_PATH)/dw_timer.c \
	$(DRV_PATH)/pwr_wdt.c \

inc_dir += \
	$(DRV_PATH) \
	$(BUILDDIR)/../../include
