/***************************************************************************
 * @file    washer.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   This is a washer animation system.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "Main.h"
#include "Port.h"
#include "washer.h"
#include "washer_cfg.h"
#include "washer_private.h"

/*--------------------------------------------------------------------*/
/* PRIVATE DATA                                                       */
/*--------------------------------------------------------------------*/
/*!< Time in the current state in seconds */
static u16 timeInState = 0;	

/*--------------------------------------------------------------------*/
/*  PUBLIC FUNCTIONS DEFINITIONS                                      */
/*--------------------------------------------------------------------*/
ERROR_t WASHER_Init(void) {
    ERROR_t error = ERROR_NO;
    
    /*!< Setting input pins */
    selectorPin     = 0;    
    startPin        = 0;   
    lowLevelPin     = 0;    
    highLevelPin    = 0;
    temperaturePin  = 0;

    /*!< Turning off output pins */
    error |= WASHER_InitState();

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

ERROR_t WASHER_Update(void) {
    ERROR_t error = ERROR_NO;

    switch(WASHER_Configs.state) {
        case WASHER_STATE_INIT:
            WASHER_InitState();
            break;
        case WASHER_STATE_FILL_DRUM:
            WASHER_FillDrumState();
            break;
        case WASHER_STATE_HEATING_WATER:
            WASHER_HeatingWaterState();
            break;
        case WASHER_STATE_WASHING_WATER:
            WASHER_WashingWaterState();
            break;
        case WASHER_STATE_DRAIN_DRUM:
            WASHER_DrainState();
            break;
        case WASHER_STATE_END:
            WASHER_EndState();
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
static ERROR_t WASHER_ControlAll(const u8 states) {
    ERROR_t error = ERROR_NO;
    
    error |= WASHER_ControlDrain(           (STATE_t)( 1 && (states & MASK_DRAIN     ) ) );
    error |= WASHER_ControlHeater(          (STATE_t)( 1 && (states & MASK_HEATER    ) ) );
    error |= WASHER_ControlValve(           (STATE_t)( 1 && (states & MASK_VALVE     ) ) );
    error |= WASHER_ControlDoorLock(        (STATE_t)( 1 && (states & MASK_DOOR_LOCK ) ) );
    error |= WASHER_ControlDetergentHatch(  (STATE_t)( 1 && (states & MASK_DETERGENT ) ) );
    error |= WASHER_ControlWasher(          (STATE_t)( 1 && (states & MASK_WASHER    ) ) );

    return error;
}

static ERROR_t WASHER_EndState(void) {
    ERROR_t error = ERROR_NO;

    WASHER_Configs.state = WASHER_STATE_END;

    /*!< Running state only at first call */
    if(0 == timeInState) {
        /*!< Turning off all output pins */
        error |= WASHER_ControlAll(ALL_OFF);

        ++timeInState;
    } else {
        /*!< Actuators is already configured at the first call, no need to do it again */
    }

    return error;
}

static ERROR_t WASHER_InitState(void) {
    ERROR_t error = ERROR_NO;
    STATE_t startSwitchState = LOW;

    WASHER_Configs.state = WASHER_STATE_INIT;

    /*!< Running state only at first call */
    if(0 == timeInState) {
        /*!< Turning off all output pins */
        error |= WASHER_ControlAll(ALL_OFF);
    } else {
        /*!< Actuators is already configured at the first call, no need to do it again */
    }
    ++timeInState;

    /*!< No timeout mechanism here */

    /*!< Reading start switch */
    error |= WASHER_ReadStartSwitch(&startSwitchState);
    if(HIGH == startSwitchState) {
        timeInState = 0;                    /*!< Reset time in state for next state */
        error |= WASHER_FillDrumState();    /*!< Go to next state */
    } else {
        /*!< Start switch is not pressed, stay in the same state */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

static ERROR_t WASHER_FillDrumState(void) {
    ERROR_t error = ERROR_NO;
    STATE_t waterLevel = LOW;

    WASHER_Configs.state = WASHER_STATE_FILL_DRUM;

    /*!< Running state only at first call */
    if(0 == timeInState) {
        /*!< Turning off all output pins, except door lock and drum valve */
        error |= WASHER_ControlAll(MASK_DOOR_LOCK | MASK_VALVE);
    } else {
        /*!< Actuators is already configured at the first call, no need to do it again */
    }
    ++timeInState;

    /*!< Checking timeout */
    if(timeInState >= MAX_FILL_DRUM_DURATION) {
       error |= ERROR_TIMEOUT;
    } else {
        /*!< Timeout not reached, do nothing */
    }

    /*!< Reading water level */
    error |= WASHER_ReadWaterLevel(&waterLevel);
    if(HIGH == waterLevel) {
        timeInState = 0;                    /*!< Reset time in state for next state */
        error |= WASHER_HeatingWaterState();    /*!< Go to next state */
    } else {
        /*!< Water level is still low, stay in the same state */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

static ERROR_t WASHER_HeatingWaterState(void) {
    ERROR_t error = ERROR_NO;
    STATE_t heatState = LOW;

    WASHER_Configs.state = WASHER_STATE_HEATING_WATER;

    /*!< Running state only at first call */
    if(0 == timeInState) {
        /*!< Turning off all output pins, except heater */
        error |= WASHER_ControlAll(MASK_HEATER);
    } else {
        /*!< Actuators is already configured at the first call, no need to do it again */
    }
    ++timeInState;

    /*!< Reading water level */
    error |= WASHER_ReadTemperature(&heatState);
    if(HIGH == heatState) {
        timeInState = 0;                        /*!< Reset time in state for next state */
        error |= WASHER_WashingWaterState();    /*!< Go to next state */
    } else {
        /*!< Water temperature is still low, stay in the same state */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

static ERROR_t WASHER_WashingWaterState(void) {
    ERROR_t error = ERROR_NO;

    WASHER_Configs.state = WASHER_STATE_WASHING_WATER;

    /*!< Running state only at first call */
    if(0 == timeInState) {
        /*!< Turning off all output pins, except washer */
        error |= WASHER_ControlAll(MASK_WASHER);
    } else {
        /*!< Actuators is already configured at the first call, no need to do it again */
    }
    ++timeInState;

    /*!< Checking if washer is finished */
    if(timeInState >= MAX_WASHING_WATER_DURATION) {
        timeInState = 0;                 /*!< Reset time in state for next state */
        error |= WASHER_DrainState();    /*!< Go to next state */
    } else {
        /*!< Washer is still running, stay in the same state */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

static ERROR_t WASHER_DrainState(void) {
    ERROR_t error = ERROR_NO;
    STATE_t waterLevel = LOW;

    WASHER_Configs.state = WASHER_STATE_DRAIN_DRUM;

    /*!< Running state only at first call */
    if(0 == timeInState) {
        /*!< Turning off all output pins, except drain drum pump */
        error |= WASHER_ControlAll(MASK_DRAIN);
    } else {
        /*!< Actuators is already configured at the first call, no need to do it again */
    }
    ++timeInState;

    /*!< Reading water level */
    error |= WASHER_ReadWaterLevel(&waterLevel);
    if(LOW == waterLevel) {
        timeInState = 0;                /*!< Reset time in state for next state */
        error |= WASHER_EndState();    /*!< Go to next state */
    } else {
        /*!< Water level is still high, stay in the same state */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Reads selector dial switch state
 * @param[out] state: pointer to return the state of the switch.
 *              \ref HIGH: switch is pressed
 *              \ref LOW: switch is not pressed
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ReadSelectoreDial(STATE_t * const state) {
    ERROR_t error = ERROR_NO;

    /*!< Reading start switch */
    *state = (STATE_t)selectorPin;

    /*!< Checking activation state of sensors, active high or active low */
    if(WASHER_Configs.activeState.selectorCotton == ACTIVE_LOW) {
        /*!< Active low, reverse logic */
        *state == HIGH? (*state = LOW): (*state = HIGH);
    } else {
        /*!< Active high, no need to reverse logic */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }
    
    return error;
}

/**********************************************************************
 * @brief    Reads start switch state
 * @param[out] state: pointer to return the state of the switch.
 *              \ref HIGH: switch is pressed
 *              \ref LOW: switch is not pressed
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ReadStartSwitch(STATE_t * const state) {
    ERROR_t error = ERROR_NO;

    /*!< Reading start switch */
    *state = (STATE_t)startPin;

    /*!< Checking activation state of sensors, active high or active low */
    if(WASHER_Configs.activeState.start == ACTIVE_LOW) {
        /*!< Active low, reverse logic */
        *state == HIGH? (*state = LOW): (*state = HIGH);
    } else {
        /*!< Active high, no need to reverse logic */
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }
    
    return error;
}

/**********************************************************************
 * @brief    Reads water level sensors state
 * @param[out] state: pointer to return the state of the sensor.
 *              \ref HIGH: Water level is high
 *              \ref LOW: Water level is low
 *              \ref NORMAL: Water level is normal (between low and high)
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ReadWaterLevel(STATE_t * const state) {
    ERROR_t error = ERROR_NO;
    bit highLevel = 0, lowLevel = 0;

    /*!< Reading water level */
    highLevel = highLevelPin;
    lowLevel  = lowLevelPin;

    /*!< Checking activation state of sensors, active high or active low */
    if(WASHER_Configs.activeState.level == ACTIVE_LOW) {
        /*!< Active low, reverse logic */
        highLevel = ! highLevel;
        lowLevel  = ! lowLevel;
    } else {
        /*!< Active high, no need to reverse logic */
    }

    if(highLevel && lowLevel) {
        *state = HIGH;
    } else if( (!highLevel) && (!lowLevel) ) {
        *state = LOW;
    } else if( (!highLevel) && lowLevel) {
        *state = NORMAL;
    } else {
        error |= ERROR_OUT_OF_RANGE;
    }

    return error;
}


/*!< Not complete function    */
static ERROR_t WASHER_ReadTemperature(STATE_t * const state) {
    ERROR_t error = ERROR_NO;
    u8 temperature = 0;

    /*!< Reading temperature */
    temperature = temperaturePin;

    /*!< Converting analog value to temperature */

    /*!< Checking if the temperature is high enough */
    if(temperature == HIGH) {
        *state = HIGH;
    } else {
        *state = LOW;
    }

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Control detergent hatch, open or close
 * @param[in] state: state to set the detergent hatch.
 *              \ref HIGH: Open the detergent hatch
 *              \ref LOW: Close the detergent hatch
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ControlDetergentHatch(const STATE_t state) {
    ERROR_t error = ERROR_NO;

    #if 1
    switch(state) {
        case LOW:
            detergentPin = ! WASHER_Configs.activeState.detergent;
            break;
        case HIGH:
            detergentPin = WASHER_Configs.activeState.detergent;
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    #elif 1
    /*!< The previous switch statement can be implemented by equation as
         the following, but equation is not readable */
    detergentPin = ( (!state)   && (!WASHER_Configs.activeState.detergent) ) || 
                   (  state     &&   WASHER_Configs.activeState.detergent  )    ;
    #endif

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Control door lock of the washer, open or close
 * @param[in] state: state to set the door lock.
 *              \ref HIGH: Open the  door lock
 *              \ref LOW: Close the  door lock
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ControlDoorLock(const STATE_t state) {
    ERROR_t error = ERROR_NO;

    #if 1
    switch(state) {
        case LOW:
            doorLockPin = ! WASHER_Configs.activeState.doorLock;
            break;
        case HIGH:
            doorLockPin = WASHER_Configs.activeState.doorLock;
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    #elif 1
    /*!< The previous switch statement can be implemented by equation as
         the following, but equation is not readable */
    doorLockPin = ( (!state)   && (!WASHER_Configs.activeState.doorLock) ) || 
                  (  state     &&   WASHER_Configs.activeState.doorLock  )    ;
    #endif

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Control washer motor, open or close
 * @param[in] state: state to set the washer motor.
 *              \ref HIGH: Open the washer motor
 *              \ref LOW: Close the washer motor
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ControlWasher(const STATE_t state) {
    ERROR_t error = ERROR_NO;

    #if 1
    switch(state) {
        case LOW:
            washerPin = ! WASHER_Configs.activeState.washer;
            break;
        case HIGH:
            washerPin = WASHER_Configs.activeState.washer;
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    #elif 1
    /*!< The previous switch statement can be implemented by equation as
         the following, but equation is not readable */
    washerPin = ( (!state)   && (!WASHER_Configs.activeState.washer) ) || 
                (  state     &&   WASHER_Configs.activeState.washer  )    ;
    #endif

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Control water drain pump, open or close
 * @param[in] state: state to set the water drain pump.
 *              \ref HIGH: Open the water drain pump
 *              \ref LOW: Close the water drain pump
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ControlDrain(const STATE_t state) {
    ERROR_t error = ERROR_NO;

    #if 1
    switch(state) {
        case LOW:
            drainPin = ! WASHER_Configs.activeState.drain;
            break;
        case HIGH:
            drainPin = WASHER_Configs.activeState.drain;
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    #elif 1
    /*!< The previous switch statement can be implemented by equation as
         the following, but equation is not readable */
    drainPin = ( (!state)   && (!WASHER_Configs.activeState.drain) ) || 
               (  state     &&   WASHER_Configs.activeState.drain  )    ;
    #endif

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Control water heater, open or close
 * @param[in] state: state to set the water heater.
 *              \ref HIGH: Open the water heater
 *              \ref LOW: Close the water heater
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ControlHeater(const STATE_t state) {
    ERROR_t error = ERROR_NO;

    #if 1
    switch(state) {
        case LOW:
            heaterPin = ! WASHER_Configs.activeState.heater;
            break;
        case HIGH:
            heaterPin = WASHER_Configs.activeState.heater;
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    #elif 1
    /*!< The previous switch statement can be implemented by equation as
         the following, but equation is not readable */
    heaterPin = ( (!state)   && (!WASHER_Configs.activeState.heater) ) || 
                (  state     &&   WASHER_Configs.activeState.heater  )    ;
    #endif

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Control water valve, open or close
 * @param[in] state: state to set the water valve.
 *              \ref HIGH: Open the water valve
 *              \ref LOW: Close the water valve
 * @return   ERROR_t: See definition of \ref ERROR_t enum for options.
 **********************************************************************/
static ERROR_t WASHER_ControlValve(const STATE_t state) {
    ERROR_t error = ERROR_NO;
    
    #if 1
    switch(state) {
        case LOW:
            valvePin = ! WASHER_Configs.activeState.valve;
            break;
        case HIGH:
            valvePin = WASHER_Configs.activeState.valve;
            break;
        default:
            error |= ERROR_ILLEGAL_PARAM;
            break;
    }
    #elif 1
    /*!< The previous switch statement can be implemented by equation as
         the following, but equation is not readable */
    valvePin = ( (!state)   && (!WASHER_Configs.activeState.valve) ) || 
               (  state     &&   WASHER_Configs.activeState.valve  )    ;
    #endif

    /*!< Error handling */
    if(ERROR_NO != error) {
        WASHER_HandleError(error);
    } else {
        /*!< No error */
    }

    return error;
}

/**********************************************************************
 * @brief    Handle the error of the washer machine
 * @param[in] error: error to handle
 **********************************************************************/
static void WASHER_HandleError(ERROR_t error) {
    switch(error) {
        case ERROR_NO:
            /*!< No error, do nothing */
            break;
        case ERROR_ILLEGAL_PARAM:
            /*!< Illegal parameter, do nothing */
            break;
        case ERROR_INIT_FAIL:
            /*!< Initialization failed, do nothing */
            break;
        case ERROR_NULL_POINTER:
            /*!< Null pointer, do nothing */
            break;
        case ERROR_TIMEOUT:
            /*!< Timeout, do nothing */
            break;
        case ERROR_BUSY:
            /*!< Busy, do nothing */
            break;
        case ERROR_NOT_INITIALIZED:
            /*!< Not initialized, do nothing */
            break;
        case ERROR_OUT_OF_RANGE:
            /*!< Out of range, do nothing */
            break;
        default:
            /*!< Ohhhhh shit, error inside error handler */
            break;
    }
}
