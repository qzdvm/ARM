/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: MAX44009. Every 2 seconds, a new
 *              Lux value is gotten and transmitted through the UART ( Baud Rate: 115200 ).
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0 ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>
#include <string.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "functions.h"
#include "variables.h"
#include "MAX44009.h"



/**@brief Constants.
 */
#define TX_BUFF_SIZE  128                         /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main( void )
{
    uint8_t  myMessage[ TX_BUFF_SIZE ];           /*!<   Message to be transmitted through the UART             */

    I2C_parameters_t        myMAX44009_I2C_parameters;
    MAX44009_status_t       aux;
    MAX44009_vector_data_t  myMAX44009_Data;


    conf_LFCLK  ();
    conf_GPIO   ();
    conf_UART   ();
    conf_RTC1   ();


    /* I2C definition   */
    myMAX44009_I2C_parameters.TWIinstance =    NRF_TWI0;
    myMAX44009_I2C_parameters.SDA         =    TWI0_SDA;
    myMAX44009_I2C_parameters.SCL         =    TWI0_SCL;
    myMAX44009_I2C_parameters.ADDR        =    MAX44009_ADDRESS_A0_VCC;
    myMAX44009_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myMAX44009_I2C_parameters.SDAport     =    NRF_GPIO;
    myMAX44009_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral  */
    aux  =   MAX44009_Init          ( myMAX44009_I2C_parameters );

    /* Configure the device: Default mode ( sample every 800ms ), CDR and TIM are automatically determined     */
    aux  =   MAX44009_Configuration ( myMAX44009_I2C_parameters, CONFIGURATION_CONT_DEFAULT_MODE, CONFIGURATION_MANUAL_DEFAULT_MODE, CONFIGURATION_CDR_CURRENT_NOT_DIVIDED, CONFIGURATION_TIM_800_MS );



    myState  =   0;                             // Reset the variable
    NRF_RTC1->TASKS_START = 1;                  // Start RTC1

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
    while( 1 )
    {
        /* Enter System ON sleep mode   */
    	__WFE();
    	/* Make sure any pending events are cleared */
    	__SEV();
    	__WFE();


        if ( myState == 1 )
        {
            NRF_GPIO->OUTCLR     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on

            /* Get Lux value    */
            aux  =   MAX44009_GetLux                    ( myMAX44009_I2C_parameters, RESOLUTION_EXTENDED_RESOLUTION, &myMAX44009_Data );

            /* Get current division ratio    */
            aux  =   MAX44009_GetCurrentDivisionRatio   ( myMAX44009_I2C_parameters, &myMAX44009_Data );

            /* Get integration time    */
            aux  =   MAX44009_GetIntegrationTime        ( myMAX44009_I2C_parameters, &myMAX44009_Data );


            /* Transmit result through the UART  */
            sprintf ( (char*)myMessage, "Lux: %ld Lux\r\n", (int32_t)( myMAX44009_Data.lux + 0.5 ) );

            NRF_UART0->TASKS_STOPRX  =   1UL;
            NRF_UART0->TASKS_STOPTX  =   1UL;
            myPtr                    =   &myMessage[0];

            NRF_UART0->TASKS_STARTTX =   1UL;
            NRF_UART0->TXD           =   *myPtr;


            /* Reset the variables   */
            myState               =  0;
            NRF_GPIO->OUTSET     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
    	}
        //__NOP();
    }
}
