#ifndef __BSP_H
#define __BSP_H

#include "stdint.h"
#include "gpio.h"

#define ON  GPIO_PIN_SET
#define OFF GPIO_PIN_RESET

void led2Ctrl(uint8_t status);
void led3Ctrl(uint8_t status);
uint8_t readKey0(void);
uint8_t readKey1(void);
#endif