/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "queue.h"
#include "bsp.h"
#include "mpu6050.h"
#include "oled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MPU6050 */
osThreadId_t MPU6050Handle;
const osThreadAttr_t MPU6050_attributes = {
  .name = "MPU6050",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for OLED_Disp */
osThreadId_t OLED_DispHandle;
const osThreadAttr_t OLED_Disp_attributes = {
  .name = "OLED_Disp",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for MPU6050_Para */
osMessageQueueId_t MPU6050_ParaHandle;
const osMessageQueueAttr_t MPU6050_Para_attributes = {
  .name = "MPU6050_Para"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartMPU6050(void *argument);
void StartOledDisp(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of MPU6050_Para */
  MPU6050_ParaHandle = osMessageQueueNew (16, sizeof(uint16_t), &MPU6050_Para_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of MPU6050 */
  MPU6050Handle = osThreadNew(StartMPU6050, NULL, &MPU6050_attributes);

  /* creation of OLED_Disp */
  OLED_DispHandle = osThreadNew(StartOledDisp, NULL, &OLED_Disp_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
      LED2_Ctrl(ON);
    osDelay(300);
      LED2_Ctrl(OFF);
    osDelay(300);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
      LED3_Ctrl(ON);
    osDelay(500);
      LED3_Ctrl(OFF);
    osDelay(500);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartMPU6050 */
/**
* @brief Function implementing the MPU6050 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartMPU6050 */
void StartMPU6050(void *argument)
{
  /* USER CODE BEGIN StartMPU6050 */
  char temperature[3] = "111";
  osStatus_t result;
  MPU_Init();

  /* Infinite loop */
  for(;;)
  {
      result = osMessageQueuePut(&MPU6050_ParaHandle,temperature,1,0);
      osDelay(20);
  }
  /* USER CODE END StartMPU6050 */
}

/* USER CODE BEGIN Header_StartOledDisp */
/**
* @brief Function implementing the OLED_Disp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOledDisp */
void StartOledDisp(void *argument)
{
    OLED_Init();
    char buffer[] = "1";
  /* USER CODE BEGIN StartOledDisp */
  /* Infinite loop */
  for(;;)
  {
      osMessageQueueGet(MPU6050_ParaHandle,buffer,1,10);
      OLED_ShowString(0,0,buffer,sizeof(buffer));
      osDelay(15);
  }
  /* USER CODE END StartOledDisp */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

