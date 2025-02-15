/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "interrupts.h"


/**
 * @brief       void USART2_IRQHandler ()
 * @details     USART2 interrupt subroutine.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void USART2_IRQHandler ( void )
{
	/* RX: RECEIVE	 */
	if ( ( USART2->ISR & USART_ISR_RXNE_Msk ) == USART_ISR_RXNE )
	{
		myState	 =	 1UL;
		myRX	 =	 USART2->RDR;
	}


	/* TX: TRANSMISSION COMPLETE	 */
	if ( ( USART2->ISR & USART_ISR_TC_Msk ) == 	USART_ISR_TC )
	{
		USART2->ICR	|=	 USART_ICR_TCCF ;						// Clear flag

		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{
			myUART_TxEnd	 =	 0UL;
			USART2->CR1		&=	~USART_CR1_TE;					// Transmitter Disabled
		}
		else
		{
			USART2->TDR	 =	 *++myPtr;
		}
	}
}
