SRC_PATH = $(BUILDDIR)/src

c_srcs += \
	$(SRC_PATH)/main.c \
	$(SRC_PATH)/cvi_gpio.c 

inc_dir += \
	 $(SRC_PATH)

asm_srcs += \
	$(SRC_PATH)/crtstart.asm

