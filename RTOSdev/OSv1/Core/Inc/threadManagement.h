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

/**
 * @brief This function is used when a new thread is created to add the thread into the process tree. The
 * function takes in the parent thread node struct - representing the thread that called for the
 * creation of the new thread - and the new child thread node struct.
 * @param parentNode: the thread node struct associated with the thread that spawned the child thread.
 * @param child: The thread node struct associated with the thread that was spawned by the parent thread.
 * @retval None
 */
void addChildNodeToParent(struct threadNode* parentNode, struct threadNode* child);

/**
 * @brief This function is responsible for adding a newly created task to the process tree under the calling
 * task. It requires the parent Node struct, the handle of the new task, and an information struct
 * with the thread information which is given to the new thread node struct. If there was no parent
 * defined, then this task will be set as the "main" task.
 * @param parent: the thread node struct associated with the thread that spawned the child thread.
 * @param handle: the thread handle of the newly spawned thread.
 * @param theInfo: threadInfo struct holding information about the newly spawned thread.
 * @retval None
 */
void initializeThreadNode(struct threadNode* parent, osThreadId_t handle, struct threadInfo* theInfo);

void checkMainModuleNodesStatus();

/**
 * @brief This function is a debugging function that will output "I am main"
 * via UART if the current running thread is the "main" thread.
 * @param None
 * @retval None
 */
void amIMain();

/**
 * @brief This is a debug function that takes in a thread handle and will output the
 * current state of that thread via UART.
 * @param handle: thread handle of the task to check the status of.
 * @retval None
 */
void threadStateDebug(osThreadId_t handle);

/**
 * @brief This is a debug function that takes in a task handle and outputs the child
 * count of the associated task via UART.
 * @param handle: thread handle of the task whose number of children treads is being checked.
 * @retval None
 */
void checkChildrenDebug(osThreadId_t handle);

/**
 * @brief This is a debug function that returns the number of children the task corresponding to
 * the passed threadNode struct.
 * @param theNode: thread node struct associated with the thread whose number of children is being checked.
 * @retval integer holding the number of children the queried thread has.
 */
int childCount(struct threadNode* theNode);

/**
 * @brief Function responsible for starting a new thread and configuring thread
 * information tracking. It requires a function pointer to the function the
 * new thread will start from, and the priority, name, and stack size. This
 * function will also add the new task to the process tree.
 * @param funptr: Function pointer to the function the new thread should start from.
 * @param tp: integer holding the priority level to set the new thread to.
 * @param tn: char pointer holding what to name the new thread.
 * @param stacksize: integer holding the size to set the stack of the new thread to.
 * @retval None
 */
void startThread(void (*funPtr), int tp, char* tn, int stackSize, void* extraData);

/**
 * @brief This function searches the process tree for the thread Node struct that correlates to a passed
 * thread handle. It uses a tree queue to do a breadth-first search for the node. If the passed handle
 * is NULL, or if no match is found, NULL is returned.
 * @param handle: the task handle of thread to find the associated node of in the process tree.
 * @retval a pointer to the associated thread node struct of the queried thread.
 */
struct threadNode* findNode(osThreadId_t handle);

/**
 * @brief This function creates and returns a pointer to a new tree queue struct. The capacity of the
 * queue is set to 100 items. The queue is used in fucntions that need to traverse the process tree.
 * @param None
 * @retval a pointer to a new tree queue struct.
 */
struct treeQueue* newTreeQueue();

/**
 * @brief This function will enqueue a thread node struct to a tree queue. If the queue is already at
 * capacity the function will return without doing anything. Otherwise the thread node will be added
 * and the queue information will be updated.
 * @param queue: the queue struct to enque a new item to.
 * @param toAdd: pointer to a thread node struct which will be added to the queue.
 * @retval None
 */
void enqueue(struct treeQueue* queue, struct threadNode* toAdd);

/**
 * @brief This function will dequeue a thread node struct from the front of a passed tree queue. If the
 * queue does not have any items in the queue, NULL is returned instead. The dequeued struct is
 * returned by the function.
 * @param queue: pointer to the tree queue struct that will have an item removed from it.
 * @retval pointer to the thread node struct that was dequeued from the provided tree queue.
 */
struct threadNode* dequeue(struct treeQueue* queue);

/**
 * @brief This function will kill the thread associated with a thread node struct
 * that it is passed. It will also kill all of the passed threads child nodes.
 * @param theNode: pointer to a thread node structure associated with the thread to be killed.
 * @retval None
 */
void killThread(struct threadNode* theNode);

/**
 * @brief This function calls the thread kill function for a thread based on
 * its thread ID.
 * @param handle: thread handle of the thread to be killed.
 * @retval None
 */
void findAndKillThread(osThreadId_t handle);

int verifyAllAlive();

/**
 * @brief This is a debug function that will output a threads name and the
 * name of all of its children via UART.
 * @param None
 * @etval None
 */
void printAllThreadInfo();

void printHelper(struct threadNode* current);

/**
 * @brief This function is used when a thread is killed, and its thread node needs to be removed from its
 * parent thread node in the process tree. It takes both thread node structs, removes the child
 * from the parent node, and edits the parent node information to be consistent with one less child.
 * @param parentNode: thread node pointer associated with the thread that spawned the doomed thread
 * @param doomed: thread node pointer associated with the thread that to be removed from the process tree.
 */
void removeChildNodeFromParent(struct threadNode* parentNode, struct threadNode* doomed);

#endif /* INC_THREADMANAGEMENT_H_ */
