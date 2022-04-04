/***************************************************************************
 * @file    washer_private.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   This is a private header file for the washer class.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef WASHER_PRIVATE_H
#define WASHER_PRIVATE_H

/*--------------------------------------------------------------------*/
/* PRIVATE DATA                                                       */
/*--------------------------------------------------------------------*/

/* Constants used by WASHER_ControlAll() */
#define ALL_OFF             ( (u8)0x00 )
#define MASK_DRAIN          ( (u8)0x01 )
#define MASK_HEATER         ( (u8)0x02 )
#define MASK_VALVE          ( (u8)0x04 )
#define MASK_DOOR_LOCK      ( (u8)0x08 )
#define MASK_DETERGENT      ( (u8)0x10 )
#define MASK_WASHER         ( (u8)0x20 )

/*!< Maximum duration of filling drum state in Seconds */
#define MAX_FILL_DRUM_DURATION      ((u16)1000) 
/*!< Maximum duration of filling detergent state in Seconds */
#define MAX_FILL_DETERGENT_DURATION ((u16)1000)
/*!< Maximum duration of heating water state in Seconds */
#define MAX_HEATING_WATER_DURATION  ((u16)1000)
/*!< Maximum duration of washing water state in Seconds */
#define MAX_WASHING_WATER_DURATION  ((u16)5)    /*!< 5 seconds, for testing */
/*!< Maximum duration of draining drum state in Seconds */
#define MAX_DRAIN_DRUM_DURATION     ((u16)1000)


/*--------------------------------------------------------------------*/
/* 	PRIVATE FUNCTIONS PROTOTYPES 									  */
/*--------------------------------------------------------------------*/
/* The following functions represent the states of the washer system */
static ERROR_t WASHER_EndState(void);
static ERROR_t WASHER_InitState(void);
static ERROR_t WASHER_FillDrumState(void);
static ERROR_t WASHER_HeatingWaterState(void);
static ERROR_t WASHER_WashingWaterState(void);
static ERROR_t WASHER_DrainState(void);

/* The following functions handle the input events of the washer system */
static ERROR_t WASHER_ReadSelectoreDial(STATE_t * const);
static ERROR_t WASHER_ReadStartSwitch(STATE_t * const);
static ERROR_t WASHER_ReadWaterLevel(STATE_t * const);
static ERROR_t WASHER_ReadTemperature(STATE_t * const);

/* The following functions represent the actions of the washer system */
static ERROR_t WASHER_ControlDetergentHatch(const STATE_t);
static ERROR_t WASHER_ControlDoorLock(const STATE_t);
static ERROR_t WASHER_ControlWasher(const STATE_t);
static ERROR_t WASHER_ControlDrain(const STATE_t);
static ERROR_t WASHER_ControlHeater(const STATE_t);
static ERROR_t WASHER_ControlValve(const STATE_t);

/* The following functions handle the error events of the washer system */
static void WASHER_HandleError(ERROR_t error);



#endif