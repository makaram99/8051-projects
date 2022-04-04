/***************************************************************************
 * @file    dinosaur.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   This is the source file for functions used in dinosaur animation 
 *          system. For more details, see \ref main.c file description.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "Main.h"
#include "Port.h"
#include "dinosaur.h"
#include "dinosaur_cfg.h"

/*--------------------------------------------------------------------*/
/* 	PRIVATE FUNCTIONS PROTOTYPES 									  */
/*--------------------------------------------------------------------*/
static ERROR_t DINOSAUR_Sleep(void);
static ERROR_t DINOSAUR_Wake(void);
static ERROR_t DINOSAUR_Growl(void);
static ERROR_t DINOSAUR_Attack(void);

/*--------------------------------------------------------------------*/
/* PUBLIC DATA                                                        */
/*--------------------------------------------------------------------*/
u16 timeInState = 0;	/*!< Time in the current state in seconds */

/*--------------------------------------------------------------------*/
/*                          PUBLIC FUNCTIONS                          */
/*--------------------------------------------------------------------*/
ERROR_t DINOSAUR_Init(void) {
    ERROR_t error = ERROR_NO;
    
    /*!< Enter the default state    */
    switch(DINOSAUR_Configs.state) {
        case DINOSAUR_SLEEPING:
            error |= DINOSAUR_Sleep();
            break;
        case DINOSAUR_WAKING:
            error |= DINOSAUR_Wake();
            break;
        case DINOSAUR_GROWLING:
            error |= DINOSAUR_Growl();
            break;
        case DINOSAUR_ATTACKING:
            error |= DINOSAUR_Attack();
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    
    return error;
}


ERROR_t DINOSAUR_Update(void) {
    ERROR_t error = ERROR_NO;

    switch(DINOSAUR_Configs.state) {
        case DINOSAUR_SLEEPING:
            if(timeInState < DINOSAUR_Configs.durations.sleeping - 1){
                if(0 == timeInState){
                    error |= DINOSAUR_Sleep();
                }
                ++timeInState;
            } else if(timeInState >= DINOSAUR_Configs.durations.sleeping - 1) {
                timeInState = 0;
                error |= DINOSAUR_Wake();
            } else {
                ++timeInState;
                error |= ERROR_OUT_OF_RANGE;
            }
            break;
        case DINOSAUR_WAKING:
            if(timeInState < DINOSAUR_Configs.durations.waking - 1){
                if(0 == timeInState){
                    error |= DINOSAUR_Wake();
                }
                ++timeInState;
            } else if(timeInState >= DINOSAUR_Configs.durations.waking - 1) {
                timeInState = 0;
                error |= DINOSAUR_Growl();
            } else {
                ++timeInState;
                error |= ERROR_OUT_OF_RANGE;
            }
            break;
        case DINOSAUR_GROWLING:
            if(timeInState < DINOSAUR_Configs.durations.growling - 1){
                if(0 == timeInState){
                    error |= DINOSAUR_Growl();
                }
                ++timeInState;
            } else if(timeInState >= DINOSAUR_Configs.durations.growling - 1) {
                timeInState = 0;
                error |= DINOSAUR_Attack();
            } else {
                ++timeInState;
                error |= ERROR_OUT_OF_RANGE;
            }
            break;
        case DINOSAUR_ATTACKING:
            if(timeInState < DINOSAUR_Configs.durations.attacking - 1){
                if(0 == timeInState){
                    error |= DINOSAUR_Attack();
                }
                ++timeInState;
            } else if(timeInState >= DINOSAUR_Configs.durations.attacking - 1) {
                timeInState = 0;
                error |= DINOSAUR_Sleep();
            } else {
                ++timeInState;
                error |= ERROR_OUT_OF_RANGE;
            }
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }

    return error;
}






/*--------------------------------------------------------------------*/
/*                 PRIVATE FUNCTIONS DEFINITIONS                      */
/*--------------------------------------------------------------------*/
/***************************************************************************
 * @brief   Enter sleep state.
 * @details For more details about working of this function, see description 
 *          of \ref main.c file.
 * @return  ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
static ERROR_t DINOSAUR_Sleep(void) {
    ERROR_t error = ERROR_NO;

    DINOSAUR_Configs.state = DINOSAUR_SLEEPING;

    redPin = 1;
    amberPin = 1;
    greenPin = 1;


    return error;
}

/***************************************************************************
 * @brief   Enter waking state. The dinosaur wakes after sleeping.
 * @details For more details about working of this function, see description 
 *          of \ref main.c file.
 * @return  ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
static ERROR_t DINOSAUR_Wake(void) {
    ERROR_t error = ERROR_NO;

    DINOSAUR_Configs.state = DINOSAUR_WAKING;

    redPin = 0;
    amberPin = 1;
    greenPin = 1;

    return error;
}

/***************************************************************************
 * @brief   Enter growling state. The dinosaur growls after waking.
 * @details For more details about working of this function, see description 
 *          of \ref main.c file.
 * @return  ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
static ERROR_t DINOSAUR_Growl(void) {
    ERROR_t error = ERROR_NO;

    DINOSAUR_Configs.state = DINOSAUR_GROWLING;

    redPin = 1;
    amberPin = 0;
    greenPin = 1;

    return error;
}

/***************************************************************************
 * @brief   Enter attacking state. The dinosaur attacks after growling.
 * @details For more details about working of this function, see description 
 *          of \ref main.c file.
 * @return  ERROR_t: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
static ERROR_t DINOSAUR_Attack(void) {
    ERROR_t error = ERROR_NO;

    DINOSAUR_Configs.state = DINOSAUR_ATTACKING;

    redPin = 1;
    amberPin = 1;
    greenPin = 0;

    return error;
}
