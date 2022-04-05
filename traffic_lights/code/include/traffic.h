/***************************************************************************
 * @file    traffic.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Traffic Light System interfaces header file. 
 *          See \ref traffic.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef TRAFFIC_H
#define TRAFFIC_H

/*--------------------------------------------------------------------*/
/* TYPE DEFINITIONS                                                   */      
/*--------------------------------------------------------------------*/
/*!< Enumeration of the traffic light sequence states */
typedef enum {
    RED,
    RED_AMBER,
    GREEN,
    AMBER
}TRAFFIC_SEQUENCE_t;




/*--------------------------------------------------------------------*/
/* PUBLIC FUNCTIONS                                                   */
/*--------------------------------------------------------------------*/
/***************************************************************************
 * @brief  Initialize the traffic light system to RED state.
 * @return ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_Init(void);

/***************************************************************************
 * @brief  De Initialize the traffic light system by turning off all the lights.
 * @return ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_DeInit(void);

/***************************************************************************
 * @brief  Update the traffic light system to the next state.
 * @return ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_Update(void);

/***************************************************************************
 * @brief   Set the traffic light color sequence to the given color sequence.
 * @param[in] color sequence: The color sequence to set. See 
 *                  \ref TRAFFIC_SEQUENCE_t for more details about the color sequences.
 * @return ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_SetColor(const TRAFFIC_SEQUENCE_t Copy_color);

/***************************************************************************
 * @brief   Get the traffic light color sequence.
 * @param[out] Copy_color: pointer to the variable to store the color sequence.
 *             See \ref TRAFFIC_SEQUENCE_t for more details about the color sequences.
 * @return ERROR_t: Error status. Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t TRAFFIC_GetColor(TRAFFIC_SEQUENCE_t * const Copy_color);


#endif          /* TRAFFIC_H */