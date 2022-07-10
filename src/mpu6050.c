#include "main.h"
#include "mpu6050.h"
#include "i2c.h"
#include "usart.h"
#include "usbd_cdc_if.h"
void MPU_Init()
{
    unsigned char CMD_Data[]={0x00,0x07,0x06,0x18,0x01};
    HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, PWR_MGMT_1, 8, CMD_Data, 8, 20);
    HAL_Delay(20);
    HAL_I2C_Mem_Write(&hi2c1, SlaveAddress, SMPLRT_DIV, 8, CMD_Data+1, 8, 20);
    HAL_Delay(20);
    HAL_I2C_Mem_Write(&hi2c1,SlaveAddress,CONFIG,8,CMD_Data+2,8,20);
    HAL_Delay(20);
    HAL_I2C_Mem_Write(&hi2c1,SlaveAddress,GYRO_CONFIG,8,CMD_Data+3,8,20);
    HAL_Delay(20);
    HAL_I2C_Mem_Write(&hi2c1,SlaveAddress,ACCEL_CONFIG,8,CMD_Data+4,8,20);
    HAL_Delay(20);
}

int16_t Get_MPU_Data(unsigned char REG_ADDR)
{
    unsigned char H;
    unsigned char L;
    HAL_I2C_Mem_Read(&hi2c1,SlaveAddress,REG_ADDR,8,&H,8,100);
    HAL_Delay(100);
    HAL_I2C_Mem_Read(&hi2c1,SlaveAddress,REG_ADDR+1,8,&L,8,100);
    HAL_Delay(100);
    return (H<<8)+L;
}

void Show_MPU_Data(void)
{
    uint16_t Accel_X = 0;
    uint16_t Accel_Y = 0;
    uint16_t Accel_Z = 0;
    Accel_X = Get_MPU_Data(ACCEL_XOUT_H);
    Accel_Y = Get_MPU_Data(ACCEL_YOUT_H);
    Accel_Z = Get_MPU_Data(ACCEL_ZOUT_H);
    CDC_Transmit_FS(&Accel_X,sizeof(Accel_X));
}