/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "string.h"
#include <stdio.h>
uint16_t num = 0;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream2;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
my_usart_type usart1_pc_type;

void hal_uart_recv_init(void)
{
	/* 1. 打开串口空闲中断 */
	__HAL_UART_ENABLE_IT(&huart1 ,UART_IT_IDLE );
	/* 2. 打开 DMA 接收 */
	HAL_UART_Receive_DMA(&huart1 ,usart1_pc_type.usart_dma_recv_buffer, USART_DMA_RECV_SIZE);
}
void hal_uart_irq_prejudge(void)
{
	uint32_t temp;
	/* 1. 判断空闲中断 */
	if(__HAL_UART_GET_FLAG(&huart1 , UART_FLAG_IDLE) != RESET)
	{
		/* 2. 清除中断 */
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		/* 3. 停止 DMA 接收 */
		HAL_UART_DMAStop(&huart1);
	    //清除 DMA 接收中断，只需读取一次状态寄存器和数据寄存器，即可实现
//		temp = huart1.Instance->ICR;
//		temp = huart1.Instance->RDR;

		/* 4. 获取 DMA 接收数据长度 : NDTR 为递减计数器，故 SIZE - NDTR*/
		temp = USART_DMA_RECV_SIZE -__HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
		usart1_pc_type.usart_dma_recv_len = temp;
		/* 5. 串口回调函数 */
		HAL_UART_RxCpltCallback(&huart1);
	}
}	
void hal_uart_recv_judge(void)
{
		/* 1. 判断是否有完整数据 */
		if(usart1_pc_type.usart_recv_flag == 1)
		{
//		/* 2. 打印数据到指定串口 */
//			HAL_UART_Transmit(&huart1 ,usart1_pc_type.usart_recv_buffer ,
//			usart1_pc_type.usart_recv_len ,100 );
		/* 2. 对接收到的数据进行处理 */	
//			if(usart1_pc_type.usart_recv_buffer[0] == 0XA7 && usart1_pc_type.usart_recv_buffer[usart1_pc_type.usart_recv_len-1] == 0x7A)
//				//判断头尾是否为对应数据，如果是执行大括号内容
//			{			    
//				  //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
//				  num ++ ;

//			   }
			/*将数据复制到usart_recv_buffer_2，方便DMA发送，如果不这么做在执行DMA发送时，清空接收缓存区会将数据清除导致发送的数据不全*/
			memcpy(usart1_pc_type.usart_recv_buffer_2 ,usart1_pc_type.usart_recv_buffer ,usart1_pc_type.usart_recv_len);
			
			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)usart1_pc_type.usart_recv_buffer_2, usart1_pc_type.usart_recv_len);//DMA发送

		/* 3. 清空接收缓存区 */
			memset(usart1_pc_type.usart_recv_buffer ,0 ,usart1_pc_type.usart_recv_len);//清除
		
		/* 4. 清空数据接收标志 */
			usart1_pc_type.usart_recv_flag = 0;
		
		/* 5. 清空数据接收长度 */
			usart1_pc_type.usart_recv_len = 0;			
		}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* 1. 判断是否为 NB 串口 */
	if(huart->Instance == huart1.Instance)
	{
		/* 2. 判断是否有未处理的数据 */
		/* 有，从地址 0+old_len 开始获取 DMA 接收区数据。 */
		if(usart1_pc_type.usart_recv_len > 0)
		{
			memcpy(&usart1_pc_type.usart_recv_buffer[usart1_pc_type.usart_recv_len] ,\
			usart1_pc_type.usart_dma_recv_buffer ,usart1_pc_type.usart_dma_recv_len);
			
			usart1_pc_type.usart_recv_len += usart1_pc_type.usart_dma_recv_len;
		}
		/* 无，从地址 0 开始获取 DMA 接收区数据。 */
		else
		{
			memcpy(usart1_pc_type.usart_recv_buffer ,usart1_pc_type.usart_dma_recv_buffer ,\
			usart1_pc_type.usart_dma_recv_len);
			
			usart1_pc_type.usart_recv_len = usart1_pc_type.usart_dma_recv_len;
		}
		/* 3. 清空 DMA 接收区 */
		memset(usart1_pc_type.usart_dma_recv_buffer ,0 ,usart1_pc_type.usart_dma_recv_len);
		/* 4. 清空 DMA 接收长度 */
		usart1_pc_type.usart_dma_recv_len = 0;
		/* 5. 置位数据接收标志 */
		usart1_pc_type.usart_recv_flag = 1;
		
		/*此函数可以在任意外部处理，避免停留在中断时间过久*/
		hal_uart_recv_judge();
	}
}
/* USER CODE END 1 */
