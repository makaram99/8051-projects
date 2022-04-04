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
 * In file washer.C 
 *********************************************************************/
/*!< Input pins */
sbit selectorPin    = P1^0;   /* Port 1 pin 0 */
sbit startPin       = P1^1;   /* Port 1 pin 1 */
sbit lowLevelPin    = P1^2;   /* Port 1 pin 2 */
sbit highLevelPin   = P1^3;   /* Port 1 pin 3 */
sbit temperaturePin = P1^4;   /* Port 1 pin 3 */

/*!< Output pins */
sbit detergentPin   = P2^0;   /* Port 2 pin 0 */
sbit doorLockPin    = P2^1;   /* Port 2 pin 1 */
sbit washerPin      = P2^2;   /* Port 2 pin 2 */
sbit drainPin       = P2^3;   /* Port 2 pin 3 */
sbit heaterPin      = P2^4;   /* Port 2 pin 4 */
sbit valvePin       = P2^5;   /* Port 2 pin 5 */


#endif  /* PORT_H */