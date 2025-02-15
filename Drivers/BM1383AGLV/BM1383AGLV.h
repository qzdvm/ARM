/**
 * @brief       BM1383AGLV.h
 * @details     Pressure Sensor IC.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  BM1383AGLV_ADDRESS     =   0b1011101          /*!<   I2C slave address byte                       */
} BM1383AGLV_address_t;



/**
  * @brief   REGISTERS
  */
typedef enum
{
  BM1383AGLV_ID1        	 =   0x0F,           /*!<  Device ID1			                         */
  BM1383AGLV_ID2         	 =   0x10,           /*!<  Device ID2								     */
  BM1383AGLV_POWER_DOWN      =   0x12,           /*!<  Power down register                           */
  BM1383AGLV_RESET	         =   0x13,           /*!<  Reset register	                             */
  BM1383AGLV_MODE_CONTROL    =   0x14,           /*!<  Mode control register                         */
  BM1383AGLV_STATUS		     =   0x19,           /*!<  Status register                               */
  BM1383AGLV_PRESSURE_MSB    =   0x1A,           /*!<  Pressure data (MSB)  		                 */
  BM1383AGLV_PRESSURE_LSB    =   0x1B,           /*!<  Pressure data (LSB)  		                 */
  BM1383AGLV_PRESSURE_XLSB   =   0x1C,           /*!<  Pressure data (XLSB)  		                 */
  BM1383AGLV_TEMPERATURE_MSB =   0x1D,           /*!<  Temperature data (MSB)                        */
  BM1383AGLV_TEMPERATURE_LSB =   0x1E            /*!<  Temperature data (LSB)                        */
} BM1383AGLV_registers_t;



/**
  * @brief   ID REGISTERS
  */
typedef enum
{
    ID_ID1           	=   0xE0,             			/*!<  ID1 value	                                */
    ID_ID2          	=   0x32              			/*!<  ID2 value	                                */
} BM1383AGLV_id_t;



/**
  * @brief   POWER_DOWN REGISTER
  */
/* PWR_DOWN <0>
 *    NOTE: Power down or active mode.
 */
typedef enum
{
	POWER_DOWN_PWR_DOWN_MASK       	=   ( 1U << 0U ),    /*!<  POWER_DOWN mask                          		*/
	POWER_DOWN_PWR_DOWN_POWER_DOWN	=   ( 0U << 0U ),    /*!<  Power down				    		[ Default ] */
	POWER_DOWN_PWR_DOWN_ACTIVE      =   ( 1U << 0U )     /*!<  Active					                		*/
} BM1383AGLV_power_down_pwr_down_t;


/**
  * @brief   RESET REGISTER
  */
/* RSTB <0>
 *    NOTE: N/A.
 */
typedef enum
{
	RESET_RSTB_MASK       			=   ( 1U << 0U ),    /*!<  RSTB mask                          		       	*/
	RESET_RSTB_RESET          		=   ( 0U << 0U ),    /*!<  Measurement control block is reset  	[ Default ] */
	RESET_RSTB_ACTIVE          		=   ( 1U << 0U )     /*!<  Measurement control block is active  		   	*/
} BM1383AGLV_reset_rstb_t;



/**
  * @brief   MODE_CONTROL REGISTER
  */
/* AVE_NUM <7:5>
 *    NOTE: Set the average number of measurement data.
 */
typedef enum
{
	MODE_CONTROL_AVE_NUM_MASK     	=   ( 0b111 << 5U ), /*!<  AVE_NUM mask                                     */
	MODE_CONTROL_AVE_NUM_SINGLE     =   ( 0b000 << 5U ), /*!<  AVE_NUM: Single                                  */
	MODE_CONTROL_AVE_NUM_AVERAGE_2  =   ( 0b001 << 5U ), /*!<  AVE_NUM: Average of  2 times         [ Default ] */
	MODE_CONTROL_AVE_NUM_AVERAGE_4  =   ( 0b010 << 5U ), /*!<  AVE_NUM: Average of  4 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_8  =   ( 0b011 << 5U ), /*!<  AVE_NUM: Average of  8 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_16 =   ( 0b100 << 5U ), /*!<  AVE_NUM: Average of 16 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_32 =   ( 0b101 << 5U ), /*!<  AVE_NUM: Average of 32 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_64 =   ( 0b110 << 5U )  /*!<  AVE_NUM: Average of 64 times                     */
} BM1383AGLV_mode_control_ave_num_t;


/* DREN <4>
 *    NOTE: DRDY pin Enable.
 */
typedef enum
{
	MODE_CONTROL_DREN_MASK     		=   ( 1U << 4U ), 	/*!<  DREN mask                             	        */
	MODE_CONTROL_DREN_DRDY_DISABLE	=   ( 0U << 4U ), 	/*!<  DRDY pin Disable                     	[ Default ] */
	MODE_CONTROL_DREN_DRDY_ENABLE 	=   ( 1U << 4U )  	/*!<  DRDY pin Enable                     				*/
} BM1383AGLV_mode_control_dren_t;


/* MODE <1:0>
 *    NOTE: Set measurement mode.
 */
typedef enum
{
	MODE_CONTROL_MODE_MASK     		=   ( 0b11 << 0U ), /*!<  MODE mask                                        */
	MODE_CONTROL_MODE_STAND_BY      =   ( 0b00 << 0U ), /*!<  Stand by                             [ Default ] */
	MODE_CONTROL_MODE_ONE_SHOT		=   ( 0b01 << 0U ), /*!<  One shot                    					   */
	MODE_CONTROL_MODE_CONTINUOUS    =   ( 0b10 << 0U )  /*!<  Continuous				                       */
} BM1383AGLV_mode_control_mode_t;


/**
  * @brief   STATUS REGISTER
  */
/* RD_DRDY <0>
 *    NOTE: Pressure and temperature measurement data ready bit.
 */
typedef enum
{
	STATUS_RD_DRDY_MASK       		=   ( 1U << 0U ),    /*!<  RD_DRDY mask                      		       						*/
	STATUS_RD_DRDY_DATA_MEASURING   =   ( 0U << 0U ),    /*!<  Measurement data output is not yet available (measuring)	[ Default ] */
	STATUS_RD_DRDY_DATA_AVAILABLE	=   ( 1U << 0U )     /*!<  Measurement data output is available								   	*/
} BM1383AGLV_reset_rd_drdy_t;





#ifndef BM1383AGLV_VECTOR_STRUCT_H
#define BM1383AGLV_VECTOR_STRUCT_H
typedef struct
{
    /* Output registers  */
    int32_t rawPressure;     						/*!<  Raw pressure                  */
    int16_t	rawTemperature;  						/*!<  Raw temperature               */

    float   pressure;        						/*!<  Pressure value                */
    float   temperature;     						/*!<  Temperature value             */

    /* Mode control	 */
    BM1383AGLV_mode_control_ave_num_t ave_num;		/*!<  Average number of measurement */
    BM1383AGLV_mode_control_dren_t	  dren;			/*!<  DRDY pin Enable	            */
    BM1383AGLV_mode_control_mode_t	  mode;			/*!<  Set measurement mode	        */

    /* Device status	 */
    BM1383AGLV_power_down_pwr_down_t pwr_down;		/*!<  Power mode		            */
    BM1383AGLV_reset_rstb_t			 rstb;			/*!<  Reset				            */
    BM1383AGLV_reset_rd_drdy_t		 rd_drdy;		/*!<  Status flag		            */

    /* Device identification   */
    uint8_t id1;        							/*!<  Device ID1                    */
    uint8_t id2;        							/*!<  Device ID2                    */
} BM1383AGLV_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    BM1383AGLV_SUCCESS     =       0,
    BM1383AGLV_FAILURE     =       1
} BM1383AGLV_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
BM1383AGLV_status_t BM1383AGLV_Init               ( I2C_parameters_t myI2Cparameters                                );

/** It gets the device identifications.
  */
BM1383AGLV_status_t BM1383AGLV_GetDeviceID        ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myDeviceID	);

/** It sets the power-down mode.
  */
BM1383AGLV_status_t BM1383AGLV_SetPowerDown       ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t myPwrDown	);

/** It gets the power-down mode.
  */
BM1383AGLV_status_t BM1383AGLV_GetPowerDown       ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myPwrDown	);

/** It sets the soft-reset.
  */
BM1383AGLV_status_t BM1383AGLV_SetSoftReset       ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t myRSTB		);

/** It gets the reset flag.
  */
BM1383AGLV_status_t BM1383AGLV_GetSoftResetFlag   ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRSTB		);

/** It sets the mode control.
  */
BM1383AGLV_status_t BM1383AGLV_SetModeControl     ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t myModeCont	);

/** It gets the mode control.
  */
BM1383AGLV_status_t BM1383AGLV_GetModeControl	  ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myModeCont	);

/** It gets the status flag.
  */
BM1383AGLV_status_t BM1383AGLV_GetStatus		  ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRD_DRDY	);

/** It gets the raw pressure.
  */
BM1383AGLV_status_t BM1383AGLV_GetRawPressure     ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRawP		);

/** It gets the raw temperature.
  */
BM1383AGLV_status_t BM1383AGLV_GetRawTemperature  ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRawT		);

/** It gets the pressure.
  */
BM1383AGLV_status_t BM1383AGLV_GetPressure     	  ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myP		);

/** It gets the temperature.
  */
BM1383AGLV_status_t BM1383AGLV_GetTemperature  	  ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myT		);
