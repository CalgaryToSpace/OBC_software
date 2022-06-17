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
#include <stdlib.h>

struct threadNode* head;

#ifndef INC_THREADMANAGEMENT_H_
#define INC_THREADMANAGEMENT_H_

void addChildNodeToParent(struct threadNode* parentNode, struct threadNode* child);

void initializeThreadNode(struct threadNode* parent, osThreadId_t handle, struct threadInfo* theInfo);

void checkMainModuleNodesStatus();

void amIMain();

void threadStateDebug(osThreadId_t handle);

void checkChildrenDebug(osThreadId_t handle);

int childCount(struct threadNode* theNode);

// Function definition of startThread, responsible for starting a new OS thread
// and populating a threadInfo struct which it returns.
void startThread(void (*funPtr), int tp, char* tn, int stackSize);

struct threadNode* findNode(osThreadId_t handle);

struct treeQueue* newTreeQueue();

void enqueue(struct treeQueue* queue, struct threadNode* toAdd);

struct threadNode* dequeue(struct treeQueue* queue);

void killThread(struct threadNode* theNode);

void findAndKillThread(osThreadId_t handle);

int verifyAllAlive();

void printAllThreadInfo();

void printHelper(struct threadNode* current);

void removeChildNodeFromParent(struct threadNode* parentNode, struct threadNode* doomed);

#endif /* INC_THREADMANAGEMENT_H_ */
