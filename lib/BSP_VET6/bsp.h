#ifndef __BSP_H
#define __BSP_H

#include "stdint.h"
#include "gpio.h"

#define ON  GPIO_PIN_SET
#define OFF GPIO_PIN_RESET

void LED2_Ctrl(uint8_t status);
void LED3_Ctrl(uint8_t status);
uint8_t Read_Key0(void);
uint8_t Read_Key1(void);
#endif