/*
 * threadManagement.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Matthew
 */


#include "threadInformation.h"
#include "threadManagement.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "uart.h"


// Fucntion that puts thread information into a struct of type threadInfo, starts
// the thread, and returns the struct. Requires a function pointer to the function
// the new thread will run, the priority to set the new thread to, the name of the
// new thread, and the stack size of the new thread.
struct threadInfo startThread(void (*funPtr), int tp, char* tn, void* arg, int stackSize){
	struct threadInfo info;
	info.threadPriority = tp;
	info.threadName = tn;

	// Use a osThreadAttr_t struct for thread initialization
	const osThreadAttr_t threadAttributes = {
			.name = tn,
			.priority = (osPriority_t) tp,
			.stack_size = stackSize
	};
	osThreadId_t threadHandle;
	info.threadHandle = &threadHandle;
	threadHandle = osThreadNew(funPtr, arg, &threadAttributes);
	return info;
}
