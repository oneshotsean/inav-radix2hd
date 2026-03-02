/*
*****************************************************************************
**
**  File        : stm32_flash_h750xb.ld
**
**  Abstract    : Linker script for STM32H750xB Device executing from
**                external QSPI NOR flash (memory-mapped at 0x90000000).
**
**                The STM32H750 has only 128K internal flash, which is
**                used by the bootloader. The main firmware runs from
**                external QSPI flash via memory-mapped (XiP) mode.
**
**                Memory layout (same as STM32H743 for RAM regions):
**                512K AXI-RAM mapped onto AXI bus on D1 domain
**                128K SRAM1 mapped on D2 domain
**                128K SRAM2 mapped on D2 domain
**                 32K SRAM3 mapped on D2 domain
**                 64K SRAM4 mapped on D3 domain
**                 64K ITCM
**                128K DTCM
**
*****************************************************************************
*/

/* Stack & Heap sizes */
_Min_Heap_Size = 0;
_Min_Stack_Size = 0x1800;

/* Entry Point */
ENTRY(Reset_Handler)

/*
0x00000000 to 0x0000FFFF   64K ITCM
0x20000000 to 0x2001FFFF  128K DTCM
0x24000000 to 0x2407FFFF  512K AXI SRAM, D1 domain, main RAM
0x30000000 to 0x3001FFFF  128K SRAM1, D2 domain
0x30020000 to 0x3003FFFF  128K SRAM2, D2 domain
0x30040000 to 0x30047FFF   32K SRAM3, D2 domain
0x38000000 to 0x3800FFFF   64K SRAM4, D3 domain
0x38800000 to 0x38800FFF    4K BACKUP SRAM, Backup domain

0x90000000 to 0x900FFFFF  1024K QSPI - isr vector + startup code
0x90100000 to 0x901FFFFF  1024K QSPI - unused placeholder for CONFIG (managed externally)
0x90200000 to 0x90FFFFFF  ~14MB QSPI - firmware code
(config and blackbox are stored in QSPI sectors beyond firmware via flash driver)
*/

/* Specify the memory areas */
MEMORY
{
    FLASH (rx)        : ORIGIN = 0x90000000, LENGTH = 1024K
    FLASH_CONFIG (r)  : ORIGIN = 0x90100000, LENGTH = 1024K

    FLASH1 (rx)       : ORIGIN = 0x90200000, LENGTH = 14336K

    ITCM_RAM (rwx)    : ORIGIN = 0x00000000, LENGTH = 64K
    DTCM_RAM (rwx)    : ORIGIN = 0x20000000, LENGTH = 128K
    RAM (rwx)         : ORIGIN = 0x24000000, LENGTH = 512K

    D2_RAM (rwx)      : ORIGIN = 0x30000000, LENGTH = 256K /* SRAM1 + SRAM2 */

    MEMORY_B1 (rx)    : ORIGIN = 0x60000000, LENGTH = 0K
}

REGION_ALIAS("STACKRAM", DTCM_RAM)
REGION_ALIAS("FASTRAM",  DTCM_RAM)
REGION_ALIAS("SLOWRAM",  D2_RAM)

INCLUDE "stm32_flash_h7_split.ld"
