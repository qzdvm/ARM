/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2018
 * @version     22/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2018
 * @version     22/July/2018   The ORIGIN   
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
  uint32_t i = 0;

  for ( i = LED1; i < ( LED4 + 1 ); i++ )
  {
    NRF_P0->OUTSET        =   ( 1U << i );

    NRF_P0->PIN_CNF[i]    =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                              ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                              ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                              ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                              ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );
  }
}


/**
 * @brief       void conf_GPIOTE  ( void )
 * @details     It configures GPIOTE channels.
 *
 *                  - LED1. IN0 ( Task ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2018
 * @version     22/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIOTE  ( void )
{
  /* Channel 0   */
  NRF_GPIOTE->CONFIG[0]    =    ( GPIOTE_CONFIG_POLARITY_Toggle   << GPIOTE_CONFIG_POLARITY_Pos   ) |
                                ( LED1                            << GPIOTE_CONFIG_PSEL_Pos       ) |
                                ( GPIOTE_CONFIG_MODE_Task         << GPIOTE_CONFIG_MODE_Pos       );


  /* Reset the task for channel 0  */
  NRF_GPIOTE->TASKS_OUT[0]  =   0;
}



/**
 * @brief       void conf_PPI  ( void )
 * @details     It interconnects NRF_TIMER0->EVENTS_COMPARE[0] with NRF_GPIOTE->TASKS_OUT[0].
 *
 *              Channel 0:
 *                  * Event: NRF_TIMER0->EVENTS_COMPARE[0].
 *                  * Task:  NRF_GPIOTE->TASKS_OUT[0].
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2018
 * @version     22/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_PPI  ( void )
{
  NRF_PPI->CH[0].EEP   =   ( uint32_t )&NRF_TIMER0->EVENTS_COMPARE[0];
  NRF_PPI->CH[0].TEP   =   ( uint32_t )&NRF_GPIOTE->TASKS_OUT[0];

  /* Enable PPI channel 0  */
  NRF_PPI->CHEN        =   ( PPI_CHEN_CH0_Enabled << PPI_CHEN_CH0_Pos );
}



/**
 * @brief       void conf_TIMER0  ( void )
 * @details     One channel. Channel zero at 0.5s.
 *
 *              Timer0:
 *                  * Prescaler:            5   ( f_Timer0 = 500kHz ( PCLK1M ) ).
 *                  * 32-bits mode.
 *                  * Interrupt DISABLED.
 *
 *                 --- Channel 0:
 *                  * Overflow:             ( 4*62500 * (f_Timer0)^(-1) ) = ( 4*62500 * (500kHz)^(-1) ) ~ 0.5s
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2018
 * @version     22/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_TIMER0  ( void )
{
  NRF_TIMER0->TASKS_STOP  =   1U;
  NRF_TIMER0->MODE        =   ( TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos );
  NRF_TIMER0->PRESCALER   =   5U;                                                                         // f_Timer0 = ( 16MHz / 2^5 ) = 500kHz
  NRF_TIMER0->BITMODE     =   ( TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos );               // 32 bit mode.
  NRF_TIMER0->TASKS_CLEAR =   1U;                                                                         // clear the task first to be usable for later.

  NRF_TIMER0->CC[0]       =   ( 4*62500 );                                                                // ( 4*62500 * (f_Timer0)^(-1) ) = ( 4*62500 * (500kHz)^(-1) ) ~ 0.5s

  NRF_TIMER0->SHORTS      =   ( TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos ); // Create an Event-Task shortcut to clear TIMER0 on COMPARE[0] and COMPARE[0] event.
}
