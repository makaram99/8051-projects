/***************************************************************************
 * @file    traffic.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   A simple traffic Light system.
 * @details It uses the cuteOS library to create tasks and schedule them.
 *          It uses TRAFFIC_Update() function to update the traffic light
 *          system. See \ref traffic.h for the implementation and sequence
 *          of the system.
 *
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "Main.h"
#include "Port.h"
#include "traffic.h"
#include "traffic_cfg.h"

/*--------------------------------------------------------------------*/
/*                          PRIVATE DATA                              */
/*--------------------------------------------------------------------*/
static TRAFFIC_SEQUENCE_t   colorSequence       = RED;  /*!< Initial colorSequence */
static u16                  timeInState = 0;    /*!< Time counter */


/*--------------------------------------------------------------------*/
/*                    PRIVATE FUNCTIONS PROTOTYPES                    */
/*--------------------------------------------------------------------*/
static ERROR_t TRAFFIC_RedSequence(void);
static ERROR_t TRAFFIC_RedAmberSequence(void);
static ERROR_t TRAFFIC_GreenSequence(void);
static ERROR_t TRAFFIC_AmberSequence(void);

static ERROR_t TRAFFIC_GenericSequence(const STATE_t red, const STATE_t amber, const STATE_t green, TRAFFIC_SEQUENCE_DURATION_t duration);







/*--------------------------------------------------------------------*/
/*                          PUBLIC FUNCTIONS                          */
/*--------------------------------------------------------------------*/
ERROR_t TRAFFIC_Init(void) {
    ERROR_t error = ERROR_NO;

    /*!< Reset the time counter */
    timeInState = 0;

    /*!< Initialize the colorSequence */
    colorSequence = RED;
    redPin   = HIGH;
    amberPin = LOW;
    greenPin = LOW;

    return error;
}

/***************************************************************************
 * @details This function does the following:
 *          * Turning off all the traffic lights.
 *          * Assign the callback function of the OS delay to NULL.
 ***************************************************************************/
ERROR_t TRAFFIC_DeInit(void) {
    ERROR_t error = ERROR_NO;

    /*!< Setting traffic light to red */
    redPin   = LOW;
    amberPin = LOW;
    greenPin = LOW;
    
    /*!< Setting callback function to NULL */
    //cuteOS_(NULL);

    return error;
}

/***************************************************************************
 * @details This function does the following:
 *          - Setting the traffic light color sequence according to the current 
 *            color sequence.
 *          - Update the OS delay for the current color sequence. 
 *          - Update the color sequence value to the next color sequence.
 *          So, when calling this function again, the color sequence will be changed.
 ***************************************************************************/
ERROR_t TRAFFIC_Update(void) {
    ERROR_t error = ERROR_NO;

    /*!< Switch on the current color sequence */
    switch(colorSequence) {
        case RED:;
            error |= TRAFFIC_RedSequence();
            break;
        case RED_AMBER:;
            error |= TRAFFIC_RedAmberSequence();
            break;
        case GREEN:;
            error |= TRAFFIC_GreenSequence();
            break;
        case AMBER:;
            error |= TRAFFIC_AmberSequence();
            break;
        default:;
            error |= ERROR_ILLEGAL_PARAM;   /*!< Illegal color sequence */
            break;
    }

    return error;
}


ERROR_t TRAFFIC_SetColor(const TRAFFIC_SEQUENCE_t Copy_color) {
    ERROR_t error = ERROR_NO;
    colorSequence = Copy_color;

    error |= TRAFFIC_Update();

    return error;
}

ERROR_t TRAFFIC_GetColor(TRAFFIC_SEQUENCE_t * const Copy_color) {
    ERROR_t error = ERROR_NO;

    *Copy_color = colorSequence;

    return error;
}






/*--------------------------------------------------------------------*/
/*                 PRIVATE FUNCTIONS DEFINITIONS                      */
/*--------------------------------------------------------------------*/
/**********************************************************************
 * @brief   Set the color of the traffic light to RED.
 * @note    This function will be called by the function TRAFFIC_Update().
 * @return  ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 **********************************************************************/
static ERROR_t TRAFFIC_RedSequence(void) {
    ERROR_t error = ERROR_NO;
    
    error |= TRAFFIC_GenericSequence(HIGH, LOW, LOW, TRAFFIC_Configs.red_duration);

    return error;
}

/**********************************************************************
 * @brief   Set the color of the traffic light to RED_AMBER.
 * @note    This function will be called by the function TRAFFIC_Update().
 * @return  ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 **********************************************************************/
static ERROR_t TRAFFIC_RedAmberSequence(void) {
    ERROR_t error = ERROR_NO;
    
    error |= TRAFFIC_GenericSequence(HIGH, HIGH, LOW, TRAFFIC_Configs.red_amber_duration);

    return error;
}

/**********************************************************************
 * @brief   Set the color of the traffic light to GREEN.
 * @note    This function will be called by the function TRAFFIC_Update().
 * @return  ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 **********************************************************************/
static ERROR_t TRAFFIC_GreenSequence(void) {
    ERROR_t error = ERROR_NO;
    
    error |= TRAFFIC_GenericSequence(LOW, LOW, HIGH, TRAFFIC_Configs.green_duration);

    return error;
}

/**********************************************************************
 * @brief   Set the color of the traffic light to AMBER.
 * @note    This function will be called by the function TRAFFIC_Update().
 * @return  ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 **********************************************************************/
static ERROR_t TRAFFIC_AmberSequence(void) {
    ERROR_t error = ERROR_NO;
    
    error |= TRAFFIC_GenericSequence(LOW, HIGH, LOW, TRAFFIC_Configs.amber_duration);

    return error;
}

/**********************************************************************
 * @brief   A generic function to set the color of the traffic light.
 * @details This function will set the color of the traffic light according to:
 *          - The passed states of each lamp.
 *          - Update the time counter.
 *          - Update the colorSequence according to the time counter
 *            for the current sequence has been completed, and reset the 
 *            time counter.
 * @param[in] redState: The state of the red lamp.
 * @param[in] amberState: The state of the amber lamp.
 * @param[in] greenState: The state of the green lamp.
 * @note The states of the lamps are either \ref HIGH or \ref LOW, member 
 *       of the global enum \ref STATE_t.
 * @param[in] duration: The duration of the current sequence in SECONDS.
 *            See \ref TRAFFIC_DURATION_t to know the duration of each 
 *            color sequence.
 * @note This function is called by the functions:
 *          - \ref TRAFFIC_RedSequence
 *          - \ref TRAFFIC_RedAmberSequence
 *          - \ref TRAFFIC_GreenSequence
 *          - \ref TRAFFIC_AmberSequence
 * @return ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 **********************************************************************/
static ERROR_t TRAFFIC_GenericSequence(const STATE_t redState, const STATE_t amberState, const STATE_t greenState, TRAFFIC_SEQUENCE_DURATION_t duration) {
    ERROR_t error = ERROR_NO;
    u8 tickTime = 0;

    /*!< Update the time counter */
    if(++timeInState >= duration) {
        timeInState = 0;            /*!< Reset the time counter */
        switch(colorSequence) {
            case RED:
                colorSequence = RED_AMBER;
                redPin   = HIGH;
                amberPin = HIGH;
                greenPin = LOW;
                break;
            case RED_AMBER:
                colorSequence = GREEN;
                redPin   = LOW;
                amberPin = LOW;
                greenPin = HIGH;
                break;
            case GREEN:
                colorSequence = AMBER;
                redPin   = LOW;
                amberPin = HIGH;
                greenPin = LOW;
                break;
            case AMBER:
                colorSequence = RED;
                redPin   = HIGH;
                amberPin = LOW;
                greenPin = LOW;
                break;
            default:
                error |= ERROR_ILLEGAL_PARAM;
                break;
        }
    } else {
        redPin   = redState;
        amberPin = amberState;
        greenPin = greenState;
    }

    return error;
}
