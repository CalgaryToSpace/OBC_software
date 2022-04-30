/*
 * taskInformation.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Matthew
 */

#include "cmsis_os.h"
#include "cmsis_os2.h"

#ifndef INC_TASKINFORMATION_H_
#define INC_TASKINFORMATION_H_

// Struct for keeping thrack of thread information
struct threadInfo{
    osThreadId_t* threadHandle;
    osThreadState_t threadState;
    int threadPriority;
    char* threadName;
};

#endif /* INC_TASKINFORMATION_H_ */
