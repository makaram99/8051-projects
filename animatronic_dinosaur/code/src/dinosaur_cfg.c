/***************************************************************************
 * @file    dinosaur_cfg.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Configurations of Traffic Light System.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include "STD_TYPES.h"
#include "Main.h"
#include "dinosaur.h"
#include "dinosaur_cfg.h"


/*-------------------------------------------------------------------------*/
/*                YOU CAN CHANGE THE FOLLOWING PARAMETERS				   */
/*-------------------------------------------------------------------------*/
/***************************************************************************
 * @brief   Initial configuration of the dinosaur system.
 ***************************************************************************/
#if 0
DINOSAUR_CONFIGS_t DINOSAUR_Configs = {
    DINOSAUR_SLEEPING,       /*!< Initial state */
    {
        255,        /*!< Sleeping duration in seconds */
        60,         /*!< Waking duration in seconds */
        40,         /*!< Growling duration in seconds */
        120,        /*!< Attacking duration in seconds */
    }
};
#elif 1
DINOSAUR_CONFIGS_t DINOSAUR_Configs = {
    DINOSAUR_SLEEPING,       /*!< Initial state */
    {
        3,        /*!< Sleeping duration in seconds */
        3,         /*!< Waking duration in seconds */
        3,         /*!< Growling duration in seconds */
        3,        /*!< Attacking duration in seconds */
    }
};
#endif
