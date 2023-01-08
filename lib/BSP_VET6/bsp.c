#include "bsp.h"

void LED3_Ctrl(uint8_t status)
{
    HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,status);
}

void LED2_Ctrl(uint8_t status)
{
    HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,status);
}

uint8_t Read_Key0(void)
{
    uint8_t value;
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin))
    {
        HAL_Delay(20);
        value = HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin);
        return value;
    }

}

uint8_t Read_Key1(void)
{
    uint8_t value;
    if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin))
    {
        HAL_Delay(20);
        value = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
        return value;
    }

}