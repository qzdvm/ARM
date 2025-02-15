/* USER CODE BEGIN Header */
/**
 * @brief       main.c
 * @details     This example shows how to work with the UART5. The LEDs will change their state if the user
 * 				sends a command through the serial port.
 *
 * 				User's command:
 * 					'1': Change the state of LED1
 * 					'2': Change the state of LED2
 * 					'3': Change the state of LED3
 * 					'4': Change the state of LED4
 *
 *				The system will send "ERROR" for other command.
 *
 *
 * 				The rest of the time, the uC is on SLEEP mode ( low-power mode ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         This firmware was tested on the B-L072Z-LRWAN1 board with STM32CubeIDE vs1.0.2. This project was generated using
 * 				SMT32CubeMX ( just to generate a template ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 * @warning     STM32L072x8/B/Z Errata sheet ( DocID027206 Rev 4 ). I2C and USART cannot wake up the device from Stop mode.
 */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "variables.h"
#include "functions.h"
#include "interrupts.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SYSTEM_CORE_CLK		2097000U
#define UART2_CLK			SYSTEM_CORE_CLK

#define TX_BUFF_SIZE  		32	                     		/*!<   UART buffer size                              		*/
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t  *myPtr;                         			/*!<  Pointer to point out myMessage                     	*/
volatile uint8_t  myRX;                         			/*!<  Data from RX UART				                     	*/
volatile uint32_t myUART_TxEnd;                     		/*!<  It indicates when an UART transmission is finished	*/
volatile uint32_t myState;                        			/*!<  State that indicates when performs a new reading		*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t  myMessage[ TX_BUFF_SIZE ];

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  Conf_GPIO  ();
  Conf_UART2 ( UART2_CLK, 115200 );
  Conf_Range ();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  __HAL_PWR_CLEAR_FLAG (PWR_FLAG_WU);
	  HAL_PWR_EnterSLEEPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if ( ( myState == 1UL ) && ( myUART_TxEnd == 0UL ) )
	  {
		  switch ( myRX )
		  {
		  case '1':
			  if ( ( GPIOB->ODR & ( 1UL << LD1 ) ) == ( 1UL << LD1 ) )
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '1';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'F';
				  myMessage[ 7 ]   =  'F';
				  myMessage[ 8 ]   =  '\n';

				  GPIOB->BRR	 =	( 1UL << LD1 );				// Turn it OFF
			  }
			  else
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '1';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'N';
				  myMessage[ 7 ]   =  '\n';

				  GPIOB->BSRR	 =	 ( 1UL << LD1 );			// Turn it ON
			  }
			  break;

		  case '2':
			  if ( ( GPIOA->ODR & ( 1UL << LD2 ) ) == ( 1UL << LD2 ) )
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '2';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'F';
				  myMessage[ 7 ]   =  'F';
				  myMessage[ 8 ]   =  '\n';

			  	  GPIOA->BRR	 =	( 1UL << LD2 );				// Turn it OFF
			  }
			  else
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '2';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'N';
				  myMessage[ 7 ]   =  '\n';

			  	  GPIOA->BSRR	 =	 ( 1UL << LD2 );			// Turn it ON
			  }
			  break;

		  case '3':
			  if ( ( GPIOB->ODR & ( 1UL << LD3 ) ) == ( 1UL << LD3 ) )
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '3';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'F';
				  myMessage[ 7 ]   =  'F';
				  myMessage[ 8 ]   =  '\n';

			  	  GPIOB->BRR	 =	( 1UL << LD3 );				// Turn it OFF
			  }
			  else
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '3';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'N';
				  myMessage[ 7 ]   =  '\n';

			   	  GPIOB->BSRR	 =	 ( 1UL << LD3 );			// Turn it ON
			  }
			  break;

		  case '4':
			  if ( ( GPIOB->ODR & ( 1UL << LD4 ) ) == ( 1UL << LD4 ) )
			  {
				  myMessage[ 0 ]   =  'L';
				  myMessage[ 1 ]   =  'E';
				  myMessage[ 2 ]   =  'D';
				  myMessage[ 3 ]   =  '4';
				  myMessage[ 4 ]   =  ' ';
				  myMessage[ 5 ]   =  'O';
				  myMessage[ 6 ]   =  'F';
				  myMessage[ 7 ]   =  'F';
				  myMessage[ 8 ]   =  '\n';

  			  	  GPIOB->BRR	 =	( 1UL << LD4 );				// Turn it OFF
  			  }
  			  else
  			  {
  				  myMessage[ 0 ]   =  'L';
  				  myMessage[ 1 ]   =  'E';
  				  myMessage[ 2 ]   =  'D';
  				  myMessage[ 3 ]   =  '4';
  				  myMessage[ 4 ]   =  ' ';
  				  myMessage[ 5 ]   =  'O';
  				  myMessage[ 6 ]   =  'N';
  				  myMessage[ 7 ]   =  '\n';

  			  	  GPIOB->BSRR	 =	 ( 1UL << LD4 );			// Turn it ON
  			  }
			  break;

		  default:
			  myMessage[ 0 ]   =  'E';
			  myMessage[ 1 ]   =  'R';
			  myMessage[ 2 ]   =  'R';
			  myMessage[ 3 ]   =  'O';
			  myMessage[ 4 ]   =  'R';
			  myMessage[ 5 ]   =  '\n';
			  break;

		  }

		  /* Transmit data through the UART	 */
		  myPtr   	 	 =   &myMessage[0];
		  USART2->TDR	 =	 *myPtr;
		  USART2->CR1	|=	 USART_CR1_TE;						// Transmitter Enabled

		  /* Reset variables	 */
		  myUART_TxEnd   =   1UL;
		  myState	 	 =	 0UL;
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
