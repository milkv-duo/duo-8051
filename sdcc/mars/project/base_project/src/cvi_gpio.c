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

#include "cvi_gpio.h"


/**
  * @brief          设置GPIO方向
  * @param[in]      base_addr: GPIO基地址
  * @param[in]      pin_num:   GPIO针脚号
  * @param[in]      direction: 方向，GPIO_DIRECTION_OUT或GPIO_DIRECTION_IN
  * @retval         void
  */
void set_gpio_direction(uint32_t base_addr,uint8_t pin_num,uint8_t direction)
{
  if(direction)
      mmio_write_32(base_addr | GPIO_SWPORTA_DDR, 
                      mmio_read_32(base_addr | GPIO_SWPORTA_DDR) | ((uint32_t)1 << pin_num));
  else mmio_write_32(base_addr | GPIO_SWPORTA_DDR, 
                      mmio_read_32(base_addr | GPIO_SWPORTA_DDR) & (~((uint32_t)1 << pin_num)));
}

/**
  * @brief          设置GPIO电平
  * @param[in]      base_addr: GPIO基地址
  * @param[in]      pin_num:   GPIO针脚号
  * @param[in]      level:     输出电平，GPIO_LEVEL_HIGH或GPIO_LEVEL_LOW
  * @retval         void
  */
void set_gpio_level(uint32_t base_addr,uint8_t pin_num,uint8_t level)
{
    if(level)
        mmio_write_32(base_addr | GPIO_SWPORTA_DR, 
                        mmio_read_32(base_addr | GPIO_SWPORTA_DR) | ((uint32_t)1 << pin_num));
    else mmio_write_32(base_addr | GPIO_SWPORTA_DR, 
                        mmio_read_32(base_addr | GPIO_SWPORTA_DR) & (~((uint32_t)1 << pin_num)));
}
