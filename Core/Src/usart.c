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
	/* 1. ???????????????? */
	__HAL_UART_ENABLE_IT(&huart1 ,UART_IT_IDLE );
	/* 2. ???? DMA ???? */
	HAL_UART_Receive_DMA(&huart1 ,usart1_pc_type.usart_dma_recv_buffer, USART_DMA_RECV_SIZE);
}
void hal_uart_irq_prejudge(void)
{
	uint32_t temp;
	/* 1. ???????????? */
	if(__HAL_UART_GET_FLAG(&huart1 , UART_FLAG_IDLE) != RESET)
	{
		/* 2. ???????? */
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		/* 3. ???? DMA ???? */
		HAL_UART_DMAStop(&huart1);
	    //???? DMA ??????????????????????????????????????????????????????
//		temp = huart1.Instance->ICR;
//		temp = huart1.Instance->RDR;

		/* 4. ???? DMA ???????????? : NDTR ???????????????? SIZE - NDTR*/
		temp = USART_DMA_RECV_SIZE -__HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
		usart1_pc_type.usart_dma_recv_len = temp;
		/* 5. ???????????? */
		HAL_UART_RxCpltCallback(&huart1);
	}
}	
void hal_uart_recv_judge(void)
{
		/* 1. ?????????????????? */
		if(usart1_pc_type.usart_recv_flag == 1)
		{
//		/* 2. ?????????????????? */
//			HAL_UART_Transmit(&huart1 ,usart1_pc_type.usart_recv_buffer ,
//			usart1_pc_type.usart_recv_len ,100 );
		/* 2. ?????????????????????? */	
//			if(usart1_pc_type.usart_recv_buffer[0] == 0XA7 && usart1_pc_type.usart_recv_buffer[usart1_pc_type.usart_recv_len-1] == 0x7A)
//				//????????????????????????????????????????????
//			{			    
//				  //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
//				  num ++ ;

//			   }
			/*????????????usart_recv_buffer_2??????DMA????????????????????????DMA????????????????????????????????????????????????????*/
			memcpy(usart1_pc_type.usart_recv_buffer_2 ,usart1_pc_type.usart_recv_buffer ,usart1_pc_type.usart_recv_len);
			
			HAL_UART_Transmit_DMA(&huart1, (uint8_t *)usart1_pc_type.usart_recv_buffer_2, usart1_pc_type.usart_recv_len);//DMA????

		/* 3. ?????????????? */
			memset(usart1_pc_type.usart_recv_buffer ,0 ,usart1_pc_type.usart_recv_len);//????
		
		/* 4. ???????????????? */
			usart1_pc_type.usart_recv_flag = 0;
		
		/* 5. ???????????????? */
			usart1_pc_type.usart_recv_len = 0;			
		}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* 1. ?????????? NB ???? */
	if(huart->Instance == huart1.Instance)
	{
		/* 2. ?????????????????????? */
		/* ?????????? 0+old_len ???????? DMA ???????????? */
		if(usart1_pc_type.usart_recv_len > 0)
		{
			memcpy(&usart1_pc_type.usart_recv_buffer[usart1_pc_type.usart_recv_len] ,\
			usart1_pc_type.usart_dma_recv_buffer ,usart1_pc_type.usart_dma_recv_len);
			
			usart1_pc_type.usart_recv_len += usart1_pc_type.usart_dma_recv_len;
		}
		/* ?????????? 0 ???????? DMA ???????????? */
		else
		{
			memcpy(usart1_pc_type.usart_recv_buffer ,usart1_pc_type.usart_dma_recv_buffer ,\
			usart1_pc_type.usart_dma_recv_len);
			
			usart1_pc_type.usart_recv_len = usart1_pc_type.usart_dma_recv_len;
		}
		/* 3. ???? DMA ?????? */
		memset(usart1_pc_type.usart_dma_recv_buffer ,0 ,usart1_pc_type.usart_dma_recv_len);
		/* 4. ???? DMA ???????? */
		usart1_pc_type.usart_dma_recv_len = 0;
		/* 5. ???????????????? */
		usart1_pc_type.usart_recv_flag = 1;
		
		/*????????????????????????????????????????????????*/
		hal_uart_recv_judge();
	}
}
/* USER CODE END 1 */
