/***************************************************************************
 * @file    washer_cfg.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configurations of Washer MAchine System.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "Main.h"
#include "washer.h"
#include "washer_cfg.h"


/*-------------------------------------------------------------------------*/
/*                YOU CAN CHANGE THE FOLLOWING PARAMETERS				   */
/*-------------------------------------------------------------------------*/
/***************************************************************************
 * @brief   Initial configuration of the washer system.
 ***************************************************************************/
WASHER_CONFIGS_t WASHER_Configs = {
    WASHER_STATE_INIT,      /*!< Initial state of the washer    */
    25,                     /*!< Threshold temperature in degrees Celsius */
    {
        ACTIVE_HIGH,       /*!< The selector dial is HIGH when it is on the cotton program */
        ACTIVE_HIGH,       /*!< The start button is HIGH when it is pressed */
        ACTIVE_HIGH,       /*!< The level sensors are HIGH when they detect water */

        ACTIVE_HIGH,       /*!< Set HIGH on the detergent pin to activate it  */
        ACTIVE_HIGH,       /*!< Set HIGH on the door lock pin to activate it  */
        ACTIVE_HIGH,       /*!< Set HIGH on the washer pin to activate it  */
        ACTIVE_HIGH,       /*!< Set HIGH on the drain pin to activate it  */
        ACTIVE_HIGH,       /*!< Set HIGH on the heater pin to activate it  */
        ACTIVE_HIGH,       /*!< Set HIGH on the valve pin to activate it  */ 
    }
};
