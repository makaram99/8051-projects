/***************************************************************************
 * @file    dinosaur.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Dinosaur Animation System interfaces header file. 
 *          See \ref dinosaur.c for more details.
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 ***************************************************************************/
#ifndef DINOSAUR_H
#define DINOSAUR_H


/*--------------------------------------------------------------------*/
/*                          API FUNCTIONS                             */
/*--------------------------------------------------------------------*/

/***************************************************************************
 * @brief   Initialize the dinosaur system according to the configurations
 *          in the \ref DINOSAUR_CONFIGS_t structure.
 * @return ERROR Status: Check the options in the global enum \ref ERROR_t.
 ***************************************************************************/
ERROR_t DINOSAUR_Init(void);

ERROR_t DINOSAUR_Update(void);



#endif          /* DINOSAUR_H */