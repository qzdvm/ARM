/**
 * @brief       MCP4725.h
 * @details     12-Bit Digital-to-Analog Converter with EEPROM Memory.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES ( NOTE1: The A2 and A1 are programmed to '00' (default), if not requested by customer.
  *                              NOTE2: On my board, the A2 and A1 are programmed to '01'. )
  */
typedef enum{
    MCP4725_ADDRESS_LOW     =   0x62,                   /*!<   A0 pin ties to GND                                            */
    MCP4725_ADDRESS_HIGH    =   0x63                    /*!<   A0 pin ties to VDD                                            */
} MCP4725_address_t;


/**
  * @brief   COMMANDS
  */
#define MCP4725_GENERAL_CALL             0x00              /*!<   The MCP4725 device acknowledges the general call address                             */

/* General Call Commands */
/**
  * @brief   GENERAL CALL COMMANDS
  */
#define MCP4725_GENERAL_CALL_RESET       0x06              /*!<  Perform an internal reset similar to a power-on-reset (POR).                          */
#define MCP4725_GENERAL_CALL_WAKE_UP     0x09              /*!<  The power-down bits of the DAC register are set to a normal operation.                */





/* Commands Registers */
/**
  * @brief   WRITE COMMAND TYPE
  */
typedef enum{
    FAST_MODE                              =   0,           /*!<  This command is used to change the DAC register. EEPROM is not affected.              */
    WRITE_DAC_REGISTER_MODE                =   1,           /*!<  Load configuration bits and data code to the DAC Register.                            */
    WRITE_DAC_AND_EEPROM_REGISTER_MODE     =   2            /*!<  Load configuration bits and data code to the DAC Register and also write the EEPROM.  */
} MCP4725_write_command_type_t;



/**
  * @brief   POWER-DOWN MODE
  */
typedef enum{
    NORMAL_MODE                                 =   0,      /*!<  Normal Mode.                                                                          */
    POWER_DOWN_1KOHM_RESISTIVE_LOAD_MODE        =   1,      /*!<  Power-Down Mode. 1 k‎Ω resistor to ground.                                             */
    POWER_DOWN_100KOHM_RESISTIVE_LOAD_MODE      =   2,      /*!<  Power-Down Mode. 100 k‎Ω resistor to ground.                                           */
    POWER_DOWN_500KOHM_RESISTIVE_LOAD_MODE      =   3       /*!<  Power-Down Mode. 500 k‎Ω resistor to ground.                                           */
} MCP4725_operation_mode_t;



/**
  * @brief   READY/#BUSY BIT
  */
typedef enum{
    EEPROM_BUSY                                 =   0,      /*!<  EEPROM write is not completed.                                                        */
    EEPROM_READY                                =   1       /*!<  EEPROM write is complete.                                                             */
} MCP4725_eeprom_status_t;




#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct{
    uint16_t EEPROM_Data;
    uint16_t DAC_Data;
} Vector_data_t;

typedef struct{
    uint32_t DAC_New_Value;
} Vector_new_dac_value_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MCP4725_SUCCESS     =       0,
    MCP4725_FAILURE     =       1
} MCP4725_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
MCP4725_status_t  MCP4725_Init                  ( I2C_parameters_t myI2Cparameters );
MCP4725_status_t  MCP4725_Reset                 ( I2C_parameters_t myI2Cparameters );
MCP4725_status_t  MCP4725_WakeUp                ( I2C_parameters_t myI2Cparameters );
MCP4725_status_t  MCP4725_PowerMode             ( I2C_parameters_t myI2Cparameters, MCP4725_write_command_type_t myWriteCMD, MCP4725_operation_mode_t myPowerMode );
MCP4725_status_t  MCP4725_SetNewValue           ( I2C_parameters_t myI2Cparameters, MCP4725_write_command_type_t myWriteCMD, Vector_new_dac_value_t myDACNewValue );
MCP4725_status_t  MCP4725_EEPROM_Status         ( I2C_parameters_t myI2Cparameters, MCP4725_eeprom_status_t* myEEPROM_Status );
MCP4725_status_t  MCP4725_GetEEPROM_Data        ( I2C_parameters_t myI2Cparameters, Vector_data_t* myEEPROMData );
MCP4725_status_t  MCP4725_GetDAC_Data           ( I2C_parameters_t myI2Cparameters, Vector_data_t* myDACData );
