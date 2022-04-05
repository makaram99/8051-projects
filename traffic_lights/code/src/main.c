/********************************************************************************
 * @file    main.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Testing cute OS.
 * @details	Traffic light system (Chapter 8 - Embedded C by Professor j. Pont). 			
 * 			See \ref traffic.c for the implementation and sequence of the system
 * 			
 * 			Application usage:
 * 			1. Initialize modules.
 *              @code 
 * 				cuteOS_Init();    
 * 				TRAFFIC_Init();	
 * 				@endcode
 * 			3. Create the tasks.
 *              @code cuteOS_TaskCreate(task1, 1000); // task1 will run every 1 second  @endcode
 *              @code cuteOS_TaskCreate(task2, 2000); // task2 will run every 2 seconds @endcode
 *          4. Start the Cute OS scheduler.
 *              @code cuteOS_Start();   @endcode
 * 			5. The application will run as follows:
 * 				5.1. Red for some seconds, then
 * 				5.2. Red-Amber for some seconds, then
 * 				5.3. Green for some seconds, then
 * 				5.4. Amberfor some seconds, then
 * 				5.5. Repeat from step 1.
 * 			The duration of each state is defined in the enum 
 * 			\ref TRAFFIC_SEQUENCE_DURATION_t in \ref traffic_cfg.h file.
 * @version 1.0.0
 * @date    2022-03-24
 * @copyright Copyright (c) 2022
 ********************************************************************************/
#include <reg52.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Main.h"
#include "Port.h"
#include "cuteOS.h"
#include "traffic.h"

void main(void) {
	/* Initialize the system */
	cuteOS_Init();					/*!< Initialize Cute OS 					*/
	TRAFFIC_Init();					/*!< Initialize the traffic light system	*/

	/*!< Create the tasks */
	cuteOS_TaskCreate(TRAFFIC_Update, 1000);	/*!< Create a task to run the traffic light system */

	/*!< Start the Cute OS scheduler	*/
	cuteOS_Start();

	/*!< The scheduler will never return from here	*/
	while(1);
}
