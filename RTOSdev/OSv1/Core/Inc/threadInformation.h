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
struct threadInfo{//kill
    osThreadState_t threadState;
    int threadPriority;//kill
    char* threadName;
};

typedef struct threadNode;

struct threadNode{
	struct threadNode* parent;
	osThreadId_t handle;
	struct threadNode** children;
	int childCount;
	osThreadState_t threadState;
	int threadPriority;//kill
	char* threadName;
};


struct treeQueue{
	int maxSize;
	int itemCount;
	int readIndex;
	int writeIndex;
	struct threadNode **items;
};




#endif /* INC_TASKINFORMATION_H_ */
