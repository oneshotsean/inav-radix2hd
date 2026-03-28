/*
*****************************************************************************
**
**  File        : stm32_flash_h750xb_for_bl.ld
**
**  Abstract    : Linker script for iNav main firmware on STM32H750xB
**                when built to run after the iNav bootloader.
**
**                Identical to stm32_flash_h750xb.ld — the firmware
**                always runs from QSPI at 0x90400000 regardless of
**                whether it was loaded by the iNav bootloader or the
**                BrainFPV bootloader, so no address relocation is needed.
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
    FLASH (rx)        : ORIGIN = 0x90400000, LENGTH = 128K
    FLASH_CONFIG (r)  : ORIGIN = 0x90420000, LENGTH = 128K

    FLASH1 (rx)       : ORIGIN = 0x90440000, LENGTH = 3840K

    ITCM_RAM (rwx)    : ORIGIN = 0x00000000, LENGTH = 64K
    DTCM_RAM (rwx)    : ORIGIN = 0x20000000, LENGTH = 128K
    RAM (rwx)         : ORIGIN = 0x24000000, LENGTH = 512K

    D2_RAM (rwx)      : ORIGIN = 0x30000000, LENGTH = 256K  /* SRAM1 + SRAM2 */

    MEMORY_B1 (rx)    : ORIGIN = 0x60000000, LENGTH = 0K
}

__firmware_start = ORIGIN(FLASH);

REGION_ALIAS("STACKRAM", DTCM_RAM)
REGION_ALIAS("FASTRAM",  DTCM_RAM)
REGION_ALIAS("SLOWRAM",  D2_RAM)

INCLUDE "stm32_flash_h7_split.ld"
