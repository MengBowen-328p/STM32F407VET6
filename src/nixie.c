#include "nixie.h"
#include "main.h"
#include "delay.h"

void I2C_START(void)
{
    HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_SET);
    Delay_us(2);
    HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_RESET);
}

void I2C_ACK(void)
{
    HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_RESET);
    Delay_us(5);
    while (HAL_GPIO_ReadPin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin)==1);
    HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_SET);
    Delay_us(2);
    HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_RESET);
}

void I2C_STOP(void)
{
    HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_RESET);
    Delay_us(2);
    HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_RESET);
    Delay_us(2);
    HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_SET);
    Delay_us(2);
    HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_SET);
}

void I2C_WriteOneByte(unsigned char Onebtye)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_RESET);
        if(Onebtye&0x01)
        {
            HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(NIXIE_DIO_GPIO_Port,NIXIE_DIO_Pin,GPIO_PIN_RESET);
        }
        Delay_us(3);
        Onebtye = Onebtye >> 1;
        HAL_GPIO_WritePin(NIXIE_CLK_GPIO_Port,NIXIE_CLK_Pin,GPIO_PIN_SET);
        Delay_us(3);
    }
}

void NIXIE_DISPLAY(void)
{
    unsigned char i;
    I2C_START();
    I2C_WriteOneByte(0x40);
    I2C_ACK();
    I2C_STOP();
    I2C_START();
    I2C_WriteOneByte(0xc0);
    I2C_ACK();
    for(i=0;i<4;i++)
    {
        I2C_WriteOneByte(0x3f);
        I2C_ACK();
    }
    I2C_STOP();
    I2C_START();
    I2C_WriteOneByte(0x89);
    I2C_ACK();
    I2C_STOP();
}
