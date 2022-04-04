/********************************************************************************
 * @file    main.c
 * @author  Mahmoud Karam (ma.karam272@gmail.com)
 * @brief   Animatronic dinosaur such as the one in Natural History Museum in London, UK.
 * @details	The Natural History Museum in London recently installed a robotic
 *          dinosaur among the fossils in their Dinosaur Gallery. 
 *          This large exhibit models a tyrannosaurus rex guarding a recent 
 *          kill: the robot is large, very loud and moves quickly. It has 
 *          proved to be very popular with visitors.
 *          
 *          In this project, we will try to animate some of the dinosaur's
 *          maneuvers:
 *          1- Sleeping: The dinosaur will be largely motionless, but will be 
 *             obviously ‘breathing’. Irregular snoring noises, or slight 
 *             movements during this time will add interest for the audience.
 *             Sleeping time is defined in \ref SLEEPING_DURATION macro.
 *          2- Waking: The dinosaur will begin to wake up. Eyelids will begin 
 *             to flicker. Breathing will become more rapid.
 *             Waking time is defined in \ref WAKING_DURATION macro.
 *          3- Growling: Eyes will suddenly open, and the dinosaur will emit a 
 *             very loud growl. Some further movement and growling will follow.
 *             Growling time is defined in \ref GROWLING_DURATION macro.
 *          4- Attacking: Rapid ‘random’ movements towards the audience. Lots 
 *             of noise (you should be able to hear this from the next floor in 
 *             the museum).
 *             Attack time is defined in \ref ATTACK_DURATION macro.
 *          
 *          Application usage:
 *          1- Initialize the OS and the dinosaur.
 *             @code 
 *              cuteOS_Init(); 
 *              DINOSAUR_Init(); 
 *             @endcode
 *          2- Create the dinosaur task with 1 second period.
 *             @code cuteOS_TaskCreate(DINOSAUR_Update, 1000); @endcode
 *          3- Start the Cute OS scheduler.
 *             @code cuteOS_Start(); @endcode
 *          4- Everything is done. The scheduler will call the dinosaur task
 *             every second to animate the dinosaur (\ref DINOSAUR_Update()).
 *          5- The dinosaur task will either remain in the previous state or
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
#include "dinosaur.h"

void main(void) {
	/* Initialize the system */
	cuteOS_Init();						/*!< Initialize Cute OS 					*/
	DINOSAUR_Init();					/*!< Initialize the dinosaur light system	*/

	/*!< Create the tasks */
	cuteOS_TaskCreate(DINOSAUR_Update, 1000);	/*!< Create a task to run the dinosaur light system */
	
	cuteOS_Start();						/*!< Start the Cute OS scheduler	*/

	/*!< The scheduler will never return from here	*/
	while(1);
}
