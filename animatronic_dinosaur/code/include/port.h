/**********************************************************************
 * @file    port.h
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Port Header file for 8052 microcontroller
 * @version 1.0.0
 * @date    2022-03-22
 * @copyright Copyright (c) 2022
 *********************************************************************/
#ifndef PORT_H
#define PORT_H

/**********************************************************************
 * In file dinosaur.C 
 *********************************************************************/
sbit redPin     = P1^0;   /* Port 1 pin 0 */
sbit amberPin   = P1^1;   /* Port 1 pin 1 */
sbit greenPin   = P1^2;   /* Port 1 pin 2 */

#endif  /* PORT_H */