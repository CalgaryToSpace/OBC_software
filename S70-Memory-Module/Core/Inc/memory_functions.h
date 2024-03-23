/*
 * memory_functions.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Saksham Puri
 */

#ifndef INC_MEMORY_FUNCTIONS_H_
#define INC_MEMORY_FUNCTIONS_H_

// -----------------------------INCLUDES-----------------------------
#include <memory_utilities.h>

// -----------------------------VARIABLES-----------------------------


// -----------------------------STEUP FUNCTIONS-----------------------------

void LFS_Config(void);
int block_device_read(const struct lfs_config*, lfs_block_t, lfs_off_t, void*,
		lfs_size_t);
int block_device_prog(const struct lfs_config*, lfs_block_t, lfs_off_t,
		const void*, lfs_size_t);
int block_device_erase(const struct lfs_config*, lfs_block_t);
int block_device_sync(const struct lfs_config*);

// -----------------------------FUNCTIONS-----------------------------

void INITIALIZE();
int8_t MOUNT();
int8_t FORCE_MOUNT();
int8_t UNMOUNT();
int8_t FORMAT();
int8_t WRITE_FILE(char *, void *, uint32_t);
int8_t READ_FILE(char *, void *, uint32_t);

#endif /* INC_MEMORY_FUNCTIONS_H_ */
