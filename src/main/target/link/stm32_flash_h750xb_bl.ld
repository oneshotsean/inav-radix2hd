/*
*****************************************************************************
**
**  File        : stm32_flash_h750xb_bl.ld
**
**  Abstract    : Linker script for the iNav bootloader on STM32H750xB.
**                The bootloader lives entirely within the 128K internal
**                flash (0x08000000).  It initialises clocks, brings up
**                the QSPI controller in memory-mapped mode, handles MSP
**                firmware-update requests, and then jumps to the main
**                firmware at 0x90000000 (QSPI XiP).
**
**                FLASH region = all 128K internal flash.
**                RAM regions  = same as STM32H743.
**
*****************************************************************************
*/

/* Stack & Heap sizes */
_Min_Heap_Size = 0;
_Min_Stack_Size = 0x1800;

/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
    FLASH (rx)        : ORIGIN = 0x08000000, LENGTH = 128K
    FLASH_CONFIG (r)  : ORIGIN = 0x08000000, LENGTH = 0     /* unused in bootloader */

    ITCM_RAM (rwx)    : ORIGIN = 0x00000000, LENGTH = 64K
    DTCM_RAM (rwx)    : ORIGIN = 0x20000000, LENGTH = 128K
    RAM (rwx)         : ORIGIN = 0x24000000, LENGTH = 512K

    D2_RAM (rwx)      : ORIGIN = 0x30000000, LENGTH = 256K  /* SRAM1 + SRAM2 */

    MEMORY_B1 (rx)    : ORIGIN = 0x60000000, LENGTH = 0K
}

/* Where the main firmware image starts (for the jump address) */
__firmware_start = 0x90000000;

REGION_ALIAS("STACKRAM", DTCM_RAM)
REGION_ALIAS("FASTRAM",  DTCM_RAM)
REGION_ALIAS("SLOWRAM",  D2_RAM)

INCLUDE "stm32_flash_h7_split.ld"
