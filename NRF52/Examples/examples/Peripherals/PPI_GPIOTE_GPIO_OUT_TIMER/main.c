/**
 * @brief       main.c
 * @details     This example shows how to work with the PPI peripheral. The LED1
 *              blinks every 500ms. PPI interconnects the TIMER0 CC[0] event with the GPIOTE task.
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2018
 * @version     22/July/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.40
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"


/**@brief Constants.
 */


/**@brief Variables.
 */



/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO   ();
  conf_GPIOTE ();
  conf_PPI    ();
  conf_TIMER0 ();

  

  NRF_TIMER0->TASKS_START  =   1U;    // Start TIMER0

//  NRF_POWER->SYSTEMOFF = 1U;
  NRF_POWER->TASKS_LOWPWR = 1U;       // Sub power mode: Low power.
  while( 1 )
  {
    /* Enter System ON sleep mode  */
    __WFE();
    /* Make sure any pending events are cleared  */
    __SEV();
    __WFE();
  }
}


/**
 * @}
 */
