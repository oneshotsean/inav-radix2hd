/*
 * This file is part of INAV.
 *
 * INAV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * INAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with INAV.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// BrainFPV RADIX 2 (analog FPV variant) - STM32H750xB @ 480MHz
//
// Hardware verified against BrainFPV/inav brainfpv branch (Jan 2025).
//
// KEY HARDWARE DIFFERENCES vs RADIX2HD:
//   - Custom FPGA co-processor for analog video sync + OSD pixel output
//     (ported from dRonin BrainRE1; requires USE_BRAINFPV_FPGA driver)
//   - Graphical gOSD rendered natively (USE_BRAINFPV_OSD, 4-bit color, QSPI)
//   - BMI270 on SPI2 (not SPI1), Flash M25P16 on SPI1, FPGA on SPI3
//   - No SD card; 32MB SPI NOR flash (32 sectors reserved for firmware)
//   - Analog video sync via STM32 COMP2 + DAC1 (BRAINFPV_OSD_USE_STM32CMP)
//   - Auto sync threshold via ADC2
//   - FPGA-driven RGB status LEDs (USE_BRAINFPV_RGB_STATUS_LED)
//   - Different LED, Beeper, UART, ADC, and PINIO pin assignments
//   - VTX fault detection pin (VTXFAULT_PIN PD10)
//   - Second PINIO for video input switching (PC15)
//
// PORTING STATUS for iNav 9:
//   - USE_BRAINFPV_FPGA driver: NOT YET PORTED — disable FPGA features until
//     the brainfpv/fpga_drv.c driver is adapted to iNav 9.
//   - USE_BRAINFPV_OSD: NOT YET PORTED — standard iNav OSD (character-based)
//     works in the meantime. gOSD requires the brainfpv/ driver directory.
//   - USE_BRAINFPV_RGB_STATUS_LED: NOT YET PORTED.
//   All other hardware (IMU, baro, flash, UARTs, ADC, outputs) is standard
//   iNav 9 and fully functional.

#define TARGET_BOARD_IDENTIFIER "RDX2"
#define USBD_PRODUCT_STRING     "BrainFPV RADIX 2"

#define EEPROM_SIZE             (4 * 4096)

// Bootloader magic number
#define BOOTLOADER_TARGET_MAGIC 0x65DF92FE

// SysTick configuration for 480MHz
#define STM32_ST_IRQ_PRIORITY   7
#define STM32_ST_USE_TIMER      13

#define CUSTOM_RESET_PIN        PC13
#define VECT_TAB_BASE           0x24000000

#define USE_MULT_CPU_IDLE_COUNTS
#define IDLE_COUNTS_PER_SEC_AT_NO_LOAD_400  18506775
#define IDLE_COUNTS_PER_SEC_AT_NO_LOAD_480  22208130

#define USE_TARGET_CONFIG

// *************** LEDs & Beeper *********************
// RADIX 2 has FPGA-driven RGB LEDs but they are not yet ported to iNav 9.
// Standard GPIO LEDs are available as fallback.
// #define USE_BRAINFPV_RGB_STATUS_LED
#define LED0                    PE6
#define LED0_INVERTED
#define LED1                    PE7
#define LED1_INVERTED

#define BEEPER                  PD14
#define BEEPER_INVERTED

// No WS2811 LED strip on RADIX 2 analog variant

// *************** PINIO ****************************
// PINIO1: VTX pit switch (cut VTX power via RC switch)
// PINIO2: Video input selector (dual camera switching)
#define USE_PINIO
#define USE_PINIOBOX
#define PINIO1_PIN              PD15
#define PINIO1_FLAGS            PINIO_FLAGS_INVERTED
#define PINIO2_PIN              PC15

// VTX fault detection (overvoltage/overcurrent on VTX power rail)
#define USE_VTXFAULT_PIN
#define VTXFAULT_PIN            PD10

// *************** SPI1 - NOR Flash (M25P16, 32MB) ***
// Flash is used as boot medium (XiP) AND for config/blackbox.
// 32 sectors (64KB each) = 2MB reserved for firmware from QSPI start.
#define USE_SPI
#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN            PA5
#define SPI1_MISO_PIN           PB4
#define SPI1_MOSI_PIN           PD7

#define USE_FLASHFS
#define USE_FLASH_M25P16
#define M25P16_SPI_BUS          BUS_SPI1
#define M25P16_CS_PIN           PE14
// 32 sectors reserved for firmware (verified against BrainFPV fork)
#define M25P16_FIRST_SECTOR     32
#define M25P16_SECTORS_SPARE_END 3

#define CONFIG_IN_EXTERNAL_FLASH
#undef USE_GYRO_REGISTER_DUMP

#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT

// *************** SPI2 - IMU (BMI270) ***************
// NOTE: BMI270 is on SPI2 on RADIX 2 (unlike RADIX2HD which uses SPI1)
#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN            PD3
#define SPI2_MISO_PIN           PC2
#define SPI2_MOSI_PIN           PC1

#define USE_IMU_BMI270
#define IMU_BMI270_ALIGN        CW0_DEG
#define BMI270_SPI_BUS          BUS_SPI2
#define BMI270_CS_PIN           PE15
#define GYRO_INT_EXTI           PE4

// *************** SPI3 - FPGA co-processor ***
// The FPGA handles: analog video sync, OSD pixel output via QSPI,
// RGB LED control, SerialRx signal inversion, 3D video config.
// Driver: brainfpv/fpga_drv.c (NOT YET PORTED to iNav 9).
// The SPI3 bus is defined so the peripheral is initialized, but
// USE_BRAINFPV_FPGA is commented out until the driver is ported.
#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN            PB3
#define SPI3_MISO_PIN           PC11
#define SPI3_MOSI_PIN           PC12
#define SPI3_NSS_PIN            PA15

// #define USE_BRAINFPV_FPGA           // Enable when fpga_drv.c is ported
// #define BRAINFPVFPGA_SPI_INSTANCE   SPI3
// #define BRAINFPVFPGA_SPI_DIVISOR    8
// #define BRAINFPVFPGA_CS_PIN         PE1
// #define BRAINFPVFPGA_RESET_PIN      PC4
// #define BRAINFPVFPGA_CLOCK_PIN      PA8

// *************** BrainFPV Graphical OSD ***
// The RADIX 2 analog OSD is a 4-bit color graphical OSD rendered by the
// STM32H750 and output through Quad-SPI to the FPGA, which overlays it
// on the analog video signal. Not a MAX7456 character OSD.
// Driver: brainfpv/brainfpv_osd.c (NOT YET PORTED to iNav 9).
// Standard iNav character OSD works in the meantime.
//
// #define USE_BRAINFPV_OSD            // Enable when brainfpv_osd.c is ported
// #define VIDEO_BITS_PER_PIXEL        4
// #define INCLUDE_VIDEO_QUADSPI
// #define VIDEO_QSPI_CLOCK_PIN        PB2
// #define VIDEO_QSPI_IO0_PIN          PD11
// #define VIDEO_QSPI_IO1_PIN          PC10
// #define VIDEO_QSPI_IO2_PIN          PE2
// #define VIDEO_QSPI_IO3_PIN          PA1
// #define VIDEO_VSYNC                 PE3
// #define VIDEO_HSYNC                 PD5
//
// OSD analog sync via STM32 comparator (COMP2) + DAC1 threshold
// #define BRAINFPV_OSD_USE_STM32CMP
// #define BRAINFPV_OSD_STM32CMP_DAC_INSTANCE  DAC1
// #define BRAINFPV_OSD_STM32CMP_CMP_INSTANCE  COMP2
// #define BRAINFPV_OSD_STM32CMP_CMP_INPUT_PIN  PE9
// #define BRAINFPV_OSD_STM32CMP_CMP_OUTPUT_PIN PE8
// #define BRAINFPV_OSD_SYNC_TH_DEFAULT  150
// #define BRAINFPV_OSD_SYNC_TH_MIN      0
// #define BRAINFPV_OSD_SYNC_TH_MAX      255
//
// Auto sync threshold detection via ADC2
// #define USE_BRAINFPV_AUTO_SYNC_THRESHOLD
// #define AUTO_SYNC_THRESHOLD_ADC_INSTANCE  ADC2
// #define AUTO_SYNC_THRESHOLD_ADC_PIN       PC3
// #define AUTO_SYNC_THRESHOLD_ADC_CHANNEL   ADC_CHANNEL_13

// *************** I2C - Baro / Mag ******************
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL                PB8
#define I2C1_SDA                PB7

#define USE_BARO
#define BARO_I2C_BUS            BUS_I2C1
// RADIX 2 ships with BMP388 or B2SMPB-02E; DPS310 also supported
#define USE_BARO_BMP280         // covers BMP280 + BMP388 (auto-detected by chip ID)
#define USE_BARO_DPS310

#define USE_MAG
#define MAG_I2C_BUS             BUS_I2C1
#define USE_MAG_ALL

#define TEMPERATURE_I2C_BUS     BUS_I2C1
#define PITOT_I2C_BUS           BUS_I2C1
#define USE_RANGEFINDER
#define RANGEFINDER_I2C_BUS     BUS_I2C1

// *************** UART *****************************
// Note: UART pin assignments differ from RADIX2HD
#define USE_VCP
#define VBUS_SENSING_PIN        PA9
#define VBUS_SENSING_ENABLED
#define USE_USB48MHZ_PLL

#define USE_UART

#define USE_UART1
#define UART1_RX_PIN            PB15
#define UART1_TX_PIN            PB6

#define USE_UART2
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2

#define USE_UART3
#define UART3_RX_PIN            PB11
#define UART3_TX_PIN            PD8

#define USE_UART4
#define UART4_RX_PIN            PD0
#define UART4_TX_PIN            PD1

#define USE_UART5
#define UART5_RX_PIN            PB12
#define UART5_TX_PIN            PB13

#define USE_UART6
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

#define SERIAL_PORT_COUNT       7   // VCP + UART1-6

// *************** ADC ******************************
// Note: ADC pin assignments differ from RADIX2HD
#define USE_ADC
#define ADC_INSTANCE            ADC1
#define ADCVREF                 3285

#define ADC_CHANNEL_1_PIN       PA6   // VBAT
#define ADC_CHANNEL_2_PIN       PB0   // Current meter
#define ADC_CHANNEL_3_PIN       PC0   // RSSI

#define VBAT_ADC_CHANNEL            ADC_CHN_1
#define CURRENT_METER_ADC_CHANNEL   ADC_CHN_2
#define RSSI_ADC_CHANNEL            ADC_CHN_3

#define BOARD_HAS_VOLTAGE_DIVIDER
#define VBAT_SCALE_DEFAULT      1760
#define CURRENT_METER_SCALE     200

// *************** Defaults *************************
#define DEFAULT_FEATURES        (FEATURE_OSD | FEATURE_TX_PROF_SEL | FEATURE_TELEMETRY | FEATURE_CURRENT_METER | FEATURE_VBAT | FEATURE_BLACKBOX)
#define DEFAULT_RX_TYPE         RX_TYPE_SERIAL
#define SERIALRX_UART           SERIAL_PORT_USART3
#define SERIALRX_PROVIDER       SERIALRX_CRSF

// *************** Output ***************************
// 8 primary motor outputs; S9/S10 on UART6 pads (disable UART6 to use)
#define MAX_PWM_OUTPUT_PORTS    8
#define USE_DSHOT
#define USE_ESC_SENSOR
#define USE_SERIALSHOT
#define USE_SERIAL_4WAY_BLHELI_INTERFACE

// *************** Port Masks ***********************
#define TARGET_IO_PORTA         (0xffff & ~(BIT(14) | BIT(13)))
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         0xffff
#define TARGET_IO_PORTE         0xffff
#define TARGET_IO_PORTF         0xffff
#define TARGET_IO_PORTG         0xffff
