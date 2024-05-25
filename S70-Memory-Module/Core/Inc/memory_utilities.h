/**
 * memory_utilities.h
 *
 * Created on: May 2, 2024
 *     Author: Saksham Puri
 */

#ifndef INC_MEMORY_UTILITIES_H_
#define INC_MEMORY_UTILITIES_H_

/*-----------------------------INCLUDES-----------------------------*/
#include "main.h"
#include "littlefs/lfs.h"
#include "littlefs/lfs_util.h"

/*-----------------------------VARIABLES-----------------------------*/
static const uint8_t FLASH_READ = 0x03;
static const uint8_t FLASH_WRITE = 0x02;
static const uint8_t FLASH_WREN = 0x06;
static const uint8_t FLASH_WRDI = 0x04;
static const uint8_t FLASH_ER4 = 0x20;
static const uint8_t FLASH_ER32 = 0x52;
static const uint8_t FLASH_ER64 = 0xd8;
static const uint8_t FLASH_ERCP = 0xC7;
static const uint8_t FLASH_STATREG1 = 0X35;
static const uint8_t FLASH_SECTOR_ERASE = 0xD8;

/*---------------------------SETUP FUNCTIONS---------------------------*/
void LFS_Config();
int block_device_read(const struct lfs_config *, lfs_block_t, lfs_off_t, void *,
                      lfs_size_t);
int block_device_prog(const struct lfs_config *, lfs_block_t, lfs_off_t,
                      const void *, lfs_size_t);
int block_device_erase(const struct lfs_config *, lfs_block_t);
int block_device_sync(const struct lfs_config *);

/*---------------------------FUNCTIONS---------------------------*/
void PULL_CS();
void SET_CS();
void READ_STATUS_REGISTER(SPI_HandleTypeDef *, uint8_t *);
void ENABLE_WREN(SPI_HandleTypeDef *);
void ENABLE_WRDI(SPI_HandleTypeDef *);
void BULK_MEM_CLEAR(SPI_HandleTypeDef *);
void MEM_CLEAR(SPI_HandleTypeDef *, uint8_t *);
void MEM_CLEAR_LFS(SPI_HandleTypeDef *, lfs_block_t);
uint8_t WRITE_LFS(SPI_HandleTypeDef *, uint8_t *, lfs_block_t, lfs_size_t);
uint8_t READ_LFS(SPI_HandleTypeDef *, uint8_t *, lfs_block_t, lfs_size_t);

void INITIALIZE(SPI_HandleTypeDef *ptr);
int8_t MOUNT();
int8_t FORCE_MOUNT();
int8_t UNMOUNT();
int8_t FORMAT();
int8_t WRITE_FILE(char *, void *, uint32_t);
int8_t READ_FILE(char *, void *, uint32_t);

#endif /* INC_MEMORY_UTILITIES_H_ */