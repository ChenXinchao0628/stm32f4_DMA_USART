# STM32-HAL库DMA串口接收发送不定长数据


本仓库包含以下内容：

1. HAL工程
2. keil5工程


## 使用说明

1. 该例程可直接烧录至STM32F4芯片运行，使用了芯片的USART1，DMA
2. 移植注意修改usart.c usart.h stm32f4xx_it.c等文件
3. 在main.c的int main(void)函数中初始化串口接收
4. 对接收到的数据进行处理在usart.c的hal_uart_recv_judge()函数中，例如将收到的数据发送回来
5. 接收数据的buff长度在usart.h的USART_DMA_RECV_SIZE  USART_RECV_SIZE中定义，默认例程为50
