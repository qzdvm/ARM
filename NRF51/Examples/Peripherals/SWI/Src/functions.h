/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "variables.h"

/* FUNCTION PROTOTYPES */
void conf_GPIO      ( void );
void conf_RTC0      ( void );
void conf_LFCLK     ( void );
void conf_SWI       ( void );
