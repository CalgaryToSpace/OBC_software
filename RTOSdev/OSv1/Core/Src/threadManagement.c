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
#include <stdio.h>



void addChildNodeToParent(struct threadNode* parentNode, struct threadNode* child){
	if(parentNode == NULL)
		return;
	if(parentNode->children == NULL){
		parentNode->children = (struct threadNode**) malloc(sizeof(struct threadNode*));
		parentNode->childCount = 1;
		parentNode->children[0] = child;
	}
	else{
		parentNode->childCount += 1;
		struct threadNode** temp = parentNode->children;
		parentNode->children = (struct threadNode**) malloc(sizeof(struct threadNode*) * parentNode->childCount);
		for(int i = 0; i < parentNode->childCount - 1; i++){
			parentNode->children[i] = temp[i];
		}
		parentNode->children[parentNode->childCount - 1] = child;
		free(temp);
	}
}

void removeChildNodeFromParent(struct threadNode* parentNode, struct threadNode* doomed){
	parentNode->childCount -= 1;
	struct threadNode** temp = parentNode->children;
	parentNode->children = (struct threadNode**) malloc(sizeof(struct threadNode*) * parentNode->childCount);
	int j = 0;
	for(int i = 0; i < parentNode->childCount + 1; i++){
		if(temp[i] == doomed){
			continue;
		}
		parentNode->children[j] = temp[i];
		j++;
	}
	free(temp);
}

void checkMainModuleNodesStatus(){

}

void initializeThreadNode(struct threadNode* parent, osThreadId_t handle, struct threadInfo* theInfo){
	struct threadNode* theNode = (struct threadNode*)malloc(sizeof(struct threadNode));
	theNode->parent = parent;
	theNode->handle = handle;
	theNode->children = NULL;
	theNode->childCount = 0;
	theNode->threadState = theInfo->threadState;
	theNode->threadPriority = theInfo->threadPriority;
	theNode->threadName = theInfo->threadName;
	if(parent == NULL)
			head = theNode;
	else
		addChildNodeToParent(parent, theNode);

}

void checkChildrenDebug(osThreadId_t handle){
	struct threadNode* theNode = findNode(handle);
	int childCount = theNode->childCount;
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
	sendUartMessage("I have ", 7);
	char childString[1];
	sprintf(childString, "%d", childCount);
	sendUartMessage(childString, 1);
	sendUartMessage(" children", 9);
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
}

int childCount(struct threadNode* theNode){
	return theNode->childCount;
}

void threadStateDebug(osThreadId_t handle){
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
	switch(osThreadGetState(handle)){
	case osThreadInactive:
		sendUartMessage("Inactive", 8);
		break;
	case osThreadReady:
		sendUartMessage("Ready", 5);
		break;
	case osThreadRunning:
		sendUartMessage("Running", 7);
		break;
	case osThreadBlocked:
		sendUartMessage("Blocked", 7);
		break;
	case osThreadTerminated:
		sendUartMessage("Terminated", 10);
		break;
	case osThreadError:
		sendUartMessage("Error", 5);
		break;
	case osThreadReserved:
		sendUartMessage("Reserved", 8);
		break;
	default:
		sendUartMessage("NADA", 4);
		break;
	}
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
}

// Function that puts thread information into a struct of type threadInfo, starts
// the thread, and returns the struct. Requires a function pointer to the function
// the new thread will run, the priority to set the new thread to, the name of the
// new thread, and the stack size of the new thread.
void startThread(void (*funPtr), int tp, char* tn, int stackSize){
	struct threadInfo info;
	info.threadPriority = tp;
	info.threadName = tn;
	osThreadAttr_t threadAttributes = {
			.name = tn,
			.priority = (osPriority_t) tp,
			.stack_size = stackSize
	};
	osThreadId_t threadHandle;
	threadHandle = osThreadNew(funPtr, NULL, &threadAttributes);
	if(head == NULL){
		initializeThreadNode(NULL, osThreadGetId(), &info);
	}
	else{
		initializeThreadNode(findNode(osThreadGetId()), threadHandle, &info);
		findNode(threadHandle);
	}
	return;
}



void amIMain(){
	if(head->handle == osThreadGetId()){
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
		sendUartMessage("I am Main", 9);
	}
}

struct treeQueue* newTreeQueue(){
	struct treeQueue *queue = (struct treeQueue*) malloc(sizeof(struct treeQueue));
	queue->maxSize = 100;
	queue->items = (struct threadNode**)malloc(sizeof(struct threadNode*) * 100);
	queue->itemCount = 0;
	queue->readIndex = 0;
	queue->writeIndex = 0;
	return queue;
};

void enqueue(struct treeQueue* queue, struct threadNode* toAdd){
	if(queue->itemCount == queue->maxSize){

		return;
	}
	queue->items[queue->writeIndex] = toAdd;
	queue->writeIndex++;
	queue->itemCount++;
	queue->writeIndex = queue->writeIndex % queue->maxSize;
	return;
}

struct threadNode* dequeue(struct treeQueue* queue){
	if(queue->itemCount == 0){

		return NULL;
	}
	struct threadNode* temp = queue->items[queue->readIndex];
	queue->readIndex++;
	queue->readIndex = queue->readIndex % queue->maxSize;
	return temp;
}

struct threadNode* findNode(osThreadId_t handle){
	if(handle == NULL){
			return NULL;
		}
	if(head->handle == handle){
		return head;
	}
	struct treeQueue* theQueue = newTreeQueue();
	enqueue(theQueue, head);
	struct threadNode* currentNode;
	while(theQueue->itemCount != 0){
		currentNode = dequeue(theQueue);
		if(currentNode->handle == handle){
			return currentNode;
		}
		else{
			for(int i = 0; i < currentNode->childCount; i++){
				enqueue(theQueue, currentNode->children[i]);
			}
		}
	}
	return NULL;
}

void killThread(struct threadNode* theNode){
	if(theNode->children == NULL){
			removeChildNodeFromParent(theNode->parent, theNode);
			osThreadTerminate(theNode->handle);
			free(theNode->children);
			free(theNode);
			return;
	}
	else{
		for(int i = 0; i < theNode->childCount; i++){
			killThread(theNode->children[i]);
		}
	}
	removeChildNodeFromParent(theNode->parent, theNode);
	osThreadTerminate(theNode->handle);
	free(theNode->children);
	free(theNode);
	return;
}


void findAndkillThread(osThreadId_t handle){
	struct threadNode* theNode = findNode(handle);
	killThread(theNode);
}

int verifyAllAlive(){

}

void printAllThreadInfo(){
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
	sendUartMessage("I am the: ", 10);
	sendUartMessage(head->threadName, 4);
	for(int i = 0; i < head->childCount; i++){
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
		sendUartMessage(head->children[i]->threadName, 3);
	}
}

void printHelper(struct threadNode* current){

}

