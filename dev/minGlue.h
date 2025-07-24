/*  Glue functions for the minIni library, adapted for FatFS on STM32
 *
 *  This file contains macros that map the function interface
 *  used by minIni to the FatFS file I/O functions for STM32 embedded systems.
 *
 *  Modified for STM32H7 with FatFS integration
 */

/* map required file I/O types and functions to FatFS library */
#include "ff.h"
#include <stdio.h>
#include <string.h>

/* Include STM32 core for cache management */
#ifdef STM32H7xx_HAL_H
#include "stm32h7xx_hal.h"
#endif

#if !defined INI_LINETERM
  #define INI_LINETERM  "\n"
#endif

#define INI_FILETYPE    FIL
#define ini_openread(filename,file)   ({ SCB_CleanInvalidateDCache(); (f_open((file), (filename), FA_READ+FA_OPEN_EXISTING) == FR_OK); })
#define ini_openwrite(filename,file)  ({ SCB_CleanInvalidateDCache(); (f_open((file), (filename), FA_WRITE+FA_CREATE_ALWAYS) == FR_OK); })
#define ini_openrewrite(filename,file) ({ SCB_CleanInvalidateDCache(); (f_open((file), (filename), FA_READ+FA_WRITE+FA_OPEN_EXISTING) == FR_OK); })
#define ini_close(file)               (f_close(file) == FR_OK)
#define ini_read(buffer,size,file)    ({ SCB_CleanInvalidateDCache(); f_gets((buffer), (size), (file)); })
#define ini_write(buffer,file)        ({ SCB_CleanInvalidateDCache(); f_puts((buffer), (file)); })
#define ini_rename(source,dest)       (f_rename((source), (dest)) == FR_OK)
#define ini_remove(filename)          (f_unlink(filename) == FR_OK)

#define INI_FILEPOS                   FSIZE_t
#define ini_tell(file,pos)            (*(pos) = f_tell((file)))
#define ini_seek(file,pos)            (f_lseek((file), *(pos)) == FR_OK)

/* for floating-point support, define additional types and functions */
#define INI_REAL                        float
#define ini_ftoa(string,value)          sprintf((string),"%f",(value))
#define ini_atof(string)                (INI_REAL)strtod((string),NULL)
