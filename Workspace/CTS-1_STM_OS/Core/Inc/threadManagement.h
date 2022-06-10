/*
 * threadManagement.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Matthew
 */
#include <threadInformation.h>
#include "threads.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"

#ifndef INC_THREADMANAGEMENT_H_
#define INC_THREADMANAGEMENT_H_

// Function definition of startThread, responsible for starting a new OS thread
// and populating a threadInfo struct which it returns.
struct threadInfo startThread(void (*funPtr), int tp, char* tn, void* arg, int stackSize);



#endif /* INC_THREADMANAGEMENT_H_ */
