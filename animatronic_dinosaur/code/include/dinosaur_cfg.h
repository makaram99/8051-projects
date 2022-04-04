/***************************************************************************
 * @file    dinosaur_cfg.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Traffic Light System interfaces header file. See \ref dinosaur.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef DINOSAUR_CFG_H
#define DINOSAUR_CFG_H

/*--------------------------------------------------------------------*/
/*	PRIVATE TYPE DEFINITIONS	    							      */
/*--------------------------------------------------------------------*/
/*!< Dinosaur states */
typedef enum{
	DINOSAUR_SLEEPING, 
	DINOSAUR_WAKING, 
	DINOSAUR_GROWLING, 
	DINOSAUR_ATTACKING,
} DINOSAUR_STATE_t;

/*!< Duration of each state in seconds */
typedef struct {
    u16 sleeping;
    u16 waking;
    u16 growling;
    u16 attacking;
} DINOSAUR_STATE_DURATION_t;

/*!< Dinosaur configuration structure */
typedef struct {
    DINOSAUR_STATE_t state;
    DINOSAUR_STATE_DURATION_t durations;
}DINOSAUR_CONFIGS_t;






/*-------------------------------------------------------------------------*/
/*                YOU MUST <<<NOT>>> CHANGE THE FOLLOWING PARAMETERS	   */
/*-------------------------------------------------------------------------*/
extern DINOSAUR_CONFIGS_t DINOSAUR_Configs;


#endif /* DINOSAUR_CFG_H */