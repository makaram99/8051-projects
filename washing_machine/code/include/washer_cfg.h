/***************************************************************************
 * @file    washer_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Washer Machine System interfaces header file. See \ref washer.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef WASHER_CFG_H
#define WASHER_CFG_H

/*-------------------------------------------------------------------------*/
/*                YOU MUST <<<NOT>>> CHANGE THE FOLLOWING 	               */
/*-------------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*	PRIVATE TYPE DEFINITIONS	    							      */
/*--------------------------------------------------------------------*/
/*!< Washing machine states */
typedef enum{
	WASHER_STATE_INIT, 
	WASHER_STATE_FILL_DRUM, 
	WASHER_STATE_HEATING_WATER,
    WASHER_STATE_WASHING_WATER,
    WASHER_STATE_DRAIN_DRUM,
    WASHER_STATE_END,
} WASHER_STATE_t;

/*!< Active state of I/Os, Active High or Active Low */
typedef struct { 
    ACTIVATION_STATUS_t selectorCotton; /*!< Which state of the selector dial to consider the cotton program */
    ACTIVATION_STATUS_t start;      /*!< Which state of start button to start the washing machine */
    ACTIVATION_STATUS_t level;      /*!< Which state the level sensors detect water */
    
    ACTIVATION_STATUS_t detergent;  /*!< Which state activates the detergent */
    ACTIVATION_STATUS_t doorLock;   /*!< Which state activates the door lock */
    ACTIVATION_STATUS_t washer;     /*!< Which state activates the washer */
    ACTIVATION_STATUS_t drain;      /*!< Which state activates the drain pump */
    ACTIVATION_STATUS_t heater;     /*!< Which state activates the heater */
    ACTIVATION_STATUS_t valve;      /*!< Which state activates the valve */
} DEVICES_ACTIVE_STATE_t;

/*!< Dinosaur configuration structure */
typedef struct {
    WASHER_STATE_t state;
    const u8 thresholdTemperature;    /*!< Threshold temperature in degrees Celsius */
    const DEVICES_ACTIVE_STATE_t activeState;
}WASHER_CONFIGS_t;


extern WASHER_CONFIGS_t WASHER_Configs;


#endif /* WASHER_CFG_H */