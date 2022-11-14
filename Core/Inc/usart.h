/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define USART_DMA_RECV_SIZE     (50)
#define USART_RECV_SIZE  		 (50)
	
	/* ������������ */
typedef struct 
{
	/* ���ݽ��ձ�־ */
	uint8_t usart_recv_flag;
	/* ���ݽ������� */
	uint16_t usart_recv_len;
	/* DMA ���ݳ��� */
	uint16_t usart_dma_recv_len;
	/* ���ݽ��������� */
	uint8_t usart_recv_buffer [USART_RECV_SIZE];
	uint8_t usart_recv_buffer_2 [USART_RECV_SIZE];//����DMA���ͣ���ֹ����ǰ���������
	/* DMA ���ݻ����� */
	uint8_t usart_dma_recv_buffer [USART_DMA_RECV_SIZE];
}my_usart_type;

extern my_usart_type usart1_pc_type;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void hal_uart_recv_judge(void);
void hal_uart_recv_init(void);
void hal_uart_irq_prejudge(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

