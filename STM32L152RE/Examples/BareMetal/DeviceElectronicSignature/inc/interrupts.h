/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l1xx.h"
#include "variables.h"
#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
void RTC_WKUP_IRQHandler ( void );
void USART2_IRQHandler 	 ( void );



/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myState;
extern volatile uint8_t  *myPtr;
extern volatile uint32_t myUART_TxEnd;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
