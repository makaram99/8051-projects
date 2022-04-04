/********************************************************************************
 * @file    main.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Washing machine system 
 * @details This project is a washing machine system. It works as the following:
 *          1- The user selects a wash program (e.g. ‘Wool’, ‘Cotton’) on the 
 * 			   selector dial.
 * 			2- The user presses the ‘Start’ switch.
 * 			3- The door lock is engaged.
 * 			4- The water valve is opened to allow water into the wash drum.
 * 			5- If the wash program involves detergent, the detergent hatch is opened. 
 * 			   When the detergent has been released, the detergent hatch is closed.
 * 			6- When the ‘full water level’ is sensed, the water valve is closed.
 * 			7- If the wash program involves warm water, the water heater is switched on. 
 * 			   When the water reaches the correct temperature, the water heater is 
 * 			   switched off.
 * 			8- The washer motor is turned on to rotate the drum. The motor then goes 
 * 			   through a series of movements, both forward and reverse (at various speeds) 
 * 			   to wash the clothes. (The precise set of movements carried out depends 
 * 			   on the wash program that the user has selected.) At the end of the 
 * 				wash cycle, the motor is stopped.
 * 			9- The pump is switched on to drain the drum. When the drum is empty, 
 * 			   the pump is switched off.
 *          
 *          Application usage:
 *          1- In \ref main() function, Initialize the OS and the washer.
 *             @code 
 *              cuteOS_Init(); 
 *              WASHER_Init(); 
 *             @endcode
 *          2- In \ref main() function, create the washer task with 1 second 
 *             period.
 *             @code cuteOS_TaskCreate(WASHER_Update, 1000); @endcode
 *          3- In \ref main() function, start the Cute OS scheduler.
 *             @code cuteOS_Start(); @endcode
 *          4- Everything is done. The scheduler will call the washer task
 *             every second to animate the washer (\ref WASHER_Update()).
 *          5- The washer task will either remain in the previous state or
 *             will change to the next state.
 * @version 1.0.0
 * @date    2022-03-24
 * @copyright Copyright (c) 2022
 * 
 * @details	Application usage:
 * 			
 ********************************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Main.h"
#include "Port.h"
#include "cuteOS.h"
#include "washer.h"

void main(void) {
	/* Initialize the system */
	cuteOS_Init();						/*!< Initialize Cute OS 					*/
	WASHER_Init();						/*!< Initialize the washer light system	*/

	/*!< Create the tasks */
	cuteOS_TaskCreate(WASHER_Update, 1000);	/*!< Create a task to run the washer light system */
	
	/*!< Start the Cute OS scheduler	*/
	cuteOS_Start();

	/*!< The scheduler will never return from here	*/
	while(1);
}
