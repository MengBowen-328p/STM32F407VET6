#ifndef _NIXIE_H_
#define _NIXIE_H_


#include "main.h"
#include "gpio.h"
#include "delay.h"

#define CLK_0 	HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_RESET)
#define CLK_1 	HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_SET)

#define DIO_0 	HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_RESET)
#define DIO_1 	HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_SET)


#endif
