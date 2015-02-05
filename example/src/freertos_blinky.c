/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "mem_tests.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Synchronizes the LED toggling to avoid racing conditions
   when both tasks wants to access at the same time */
static void safe_Board_LED_Set(uint8_t LEDNumber, bool On)
{
    Board_LED_Set(LEDNumber, On);
}

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 and LED1 state is off */
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	prvSetupHardware();

	DEBUGOUT("MEM Test Started");

#define SDRAM_SIZE               0x2000000 // 32MB available on dev board
#define SDRAM_BASE               0x28000000 /*CS0*/

	MEM_TEST_SETUP_T test_setup;

	test_setup.bytes = 4 * 1024; //SDRAM_SIZE;
	test_setup.start_addr = (uint32_t *)SDRAM_BASE;

	printf("doing mem test walk 1");
	bool result = mem_test_walking1(&test_setup);
	printf("mem test walk 1 RES:%d", result);

	while(1) {

	}
	/* Should never arrive here */
	return 1;
}
