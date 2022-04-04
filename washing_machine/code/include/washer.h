/***************************************************************************
 * @file    washer.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Dinosaur Animation System interfaces header file. 
 *          See \ref washer.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef WASHER_H
#define WASHER_H


/*--------------------------------------------------------------------*/
/*                          API FUNCTIONS                             */
/*--------------------------------------------------------------------*/

/***************************************************************************
 * @brief   Initialize the washer system according to the configurations
 *          in the \ref WASHER_CONFIGS_t structure.
 * @return ERROR Status: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t WASHER_Init(void);

ERROR_t WASHER_Update(void);



#endif          /* WASHER_H */