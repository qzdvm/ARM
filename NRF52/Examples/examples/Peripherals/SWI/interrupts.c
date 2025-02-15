/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void RTC0_IRQHandler ()
 * @details     RTC0 subroutine. It enables one of the software interrupts
 *              according to the 'chooseLEDON' variable every 125ms.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         All the LEDs are connected like Common Anode.
 * @warning     N/A
 */
void RTC0_IRQHandler()
{
    if ( ( NRF_RTC0->EVENTS_TICK != 0 ) && ( ( NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Enabled ) != 0 ) )
    {
        NRF_RTC0->EVENTS_TICK    =   0;                                     // Reset flag
        
        /* Turn all the LEDs off */
        NRF_P0->OUTSET =  ( ( 1UL << LED1 ) | ( 1UL << LED2 ) | ( 1UL << LED3 ) | ( 1UL << LED4 ) );

        /* Enable the right software interrupt */
        switch ( chooseLEDON ){
        // LED1 ON
        default:
        case LED1_ON:
            chooseLEDON  =   LED2_ON;
            NVIC_SetPendingIRQ ( SWI5_IRQn );
            break;

        case LED2_ON:
        // LED2 ON
            chooseLEDON  =   LED3_ON;
            NVIC_SetPendingIRQ ( SWI1_IRQn );
            break;

        case LED3_ON:
        // LED3 ON
            chooseLEDON  =   LED4_ON;
            NVIC_SetPendingIRQ ( SWI3_IRQn );
            break;

        case LED4_ON:
        // LED4 ON
            chooseLEDON  =   LED1_ON;
            NVIC_SetPendingIRQ ( SWI4_IRQn );
            break;
        }
    }
}



/**
 * @brief       void SWI5_EGU5_IRQHandler ()
 * @details     SWI5 subroutine. It turns the LED1 on.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         The LED1 is connected like Common Anode.
 * @warning     N/A
 */
void SWI5_EGU5_IRQHandler()
{
    NRF_P0->OUTCLR =  ( 1UL << LED1 );

    NVIC_ClearPendingIRQ ( SWI5_IRQn );             // Clear flag
}


/**
 * @brief       void SWI1_EGU1_IRQHandler ()
 * @details     SWI1 subroutine. It turns the LED2 on.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         The LED2 is connected like Common Anode.
 * @warning     N/A
 */
void SWI1_EGU1_IRQHandler()
{
    NRF_P0->OUTCLR =  ( 1UL << LED2 );

    NVIC_ClearPendingIRQ ( SWI1_IRQn );             // Clear flag
}


/**
 * @brief       void SWI3_EGU3_IRQHandler ()
 * @details     SWI3 subroutine. It turns the LED3 on.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     N/A
 */
void SWI3_EGU3_IRQHandler()
{
    NRF_P0->OUTCLR =  ( 1UL << LED3 );

    NVIC_ClearPendingIRQ ( SWI3_IRQn );             // Clear flag
}


/**
 * @brief       void SWI4_EGU4_IRQHandler ()
 * @details     SWI4 subroutine. It turns the LED4 on.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
 * @pre         The LED4 is connected like Common Anode.
 * @warning     N/A
 */
void SWI4_EGU4_IRQHandler()
{
    NRF_P0->OUTCLR =  ( 1UL << LED4 );

    NVIC_ClearPendingIRQ ( SWI4_IRQn );             // Clear flag
}
