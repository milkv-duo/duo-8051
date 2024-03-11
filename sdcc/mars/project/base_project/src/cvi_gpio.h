/**
  ******************************************************************************
  * @file       cvi_gpio.c/h
  * @brief      cvi18xx系列芯片8051 GPIO驱动
  * @note       milkv@rjgawuie
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ******************************************************************************
  */
#include "stdio.h"
#include "cvi_reg.h"


#define GPIO0_BASE 0x03020000
#define GPIO1_BASE 0x03021000
#define GPIO2_BASE 0x03022000
#define GPIO3_BASE 0x03023000

#define GPIO_SWPORTA_DR 0x000
#define GPIO_SWPORTA_DDR 0x004

#define GPIO_DIRECTION_IN   0
#define GPIO_DIRECTION_OUT  1

#define GPIO_LEVEL_HIGH     1
#define GPIO_LEVEL_LOW      0


void set_gpio_direction(uint32_t base_addr,uint8_t pin_num,uint8_t direction);
void set_gpio_level(uint32_t base_addr,uint8_t pin_num,uint8_t level);

