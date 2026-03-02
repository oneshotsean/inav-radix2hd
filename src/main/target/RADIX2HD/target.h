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

#define TARGET_BOARD_IDENTIFIER "RDX2HD"
#define USBD_PRODUCT_STRING     "BrainFPV RADIX 2 HD"

// Config stored in external QSPI NOR flash via M25P16 driver.
// EEPROM_SIZE is the in-RAM buffer used by the config streamer.
#define EEPROM_SIZE             (4 * 4096)

#define USE_TARGET_CONFIG

// *************** LEDs & Beeper *********************
#define LED0                    PA7
#define LED1                    PE5

#define BEEPER                  PE4
#define BEEPER_INVERTED

// *************** LED Strip *************************
#define USE_LED_STRIP
// WS2811 output has a hardware inverter, signal is inverted
#define WS2811_PIN              PA3

// *************** PINIO ****************************
// PINIO1: HD video regulator enable (active-low / inverted)
#define USE_PINIO
#define USE_PINIOBOX
#define PINIO1_PIN              PC14
#define PINIO1_FLAGS            PINIO_FLAGS_INVERTED

// *************** SPI1 - IMU (BMI270) ***************
#define USE_SPI
#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN            PA5
#define SPI1_MISO_PIN           PB4
#define SPI1_MOSI_PIN           PD7

#define USE_IMU_BMI270
#define IMU_BMI270_ALIGN        CW0_DEG
#define BMI270_SPI_BUS          BUS_SPI1
#define BMI270_CS_PIN           PD3
#define GYRO_INT_EXTI           PB3

// *************** QuadSPI - NOR Flash (config + blackbox) ***
// Flash is also used as the boot medium (QSPI XiP at 0x90000000).
// The first M25P16_FIRST_SECTOR sectors are reserved for the firmware.
// Config and blackbox use the remaining sectors.
#define USE_QUADSPI
#define USE_QUADSPI_DEVICE_1
#define QUADSPI1_SCK_PIN        PB2
#define QUADSPI1_BK1_IO0_PIN    PD11
#define QUADSPI1_BK1_IO1_PIN    PD12
#define QUADSPI1_BK1_IO2_PIN    PE2
#define QUADSPI1_BK1_IO3_PIN    PA1
#define QUADSPI1_BK1_CS_PIN     PB10

#define QUADSPI1_BK2_IO0_PIN    NONE
#define QUADSPI1_BK2_IO1_PIN    NONE
#define QUADSPI1_BK2_IO2_PIN    NONE
#define QUADSPI1_BK2_IO3_PIN    NONE
#define QUADSPI1_BK2_CS_PIN     NONE

#define QUADSPI1_MODE           QUADSPI_MODE_BK1_ONLY
#define QUADSPI1_CS_FLAGS       (QUADSPI_BK1_CS_HARDWARE | QUADSPI_BK2_CS_NONE | QUADSPI_CS_MODE_LINKED)

#define USE_FLASHFS
#define USE_FLASH_M25P16
// Sectors 0 to (M25P16_FIRST_SECTOR - 1) are reserved for firmware.
// With 4KB sectors, 512 sectors = 2MB for firmware image.
#define M25P16_FIRST_SECTOR     512
#define M25P16_SECTORS_SPARE_END 3
#define M25P16_QUADSPI_DEVICE   QUADSPIDEV_1

// Config is stored in the external QSPI flash via the flash driver.
#define CONFIG_IN_EXTERNAL_FLASH
#undef USE_GYRO_REGISTER_DUMP

#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT

// *************** SD Card (SDIO) ********************
#define USE_SDCARD
#define USE_SDCARD_SDIO
#define SDCARD_SDIO_DEVICE      SDIODEV_1
#define SDCARD_SDIO_4BIT
#define SDCARD_DETECT_INVERTED
#define SDCARD_DETECT_PIN       PD9

#define ENABLE_BLACKBOX_LOGGING_ON_SDCARD_BY_DEFAULT

// *************** I2C - Baro / Mag ******************
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL                PB6
#define I2C1_SDA                PB7

#define USE_BARO
#define BARO_I2C_BUS            BUS_I2C1
#define USE_BARO_DPS310
#define USE_BARO_MS5611

#define USE_MAG
#define MAG_I2C_BUS             BUS_I2C1
#define USE_MAG_ALL

#define TEMPERATURE_I2C_BUS     BUS_I2C1
#define PITOT_I2C_BUS           BUS_I2C1
#define USE_RANGEFINDER
#define RANGEFINDER_I2C_BUS     BUS_I2C1

// *************** UART *****************************
#define USE_VCP
#define VBUS_SENSING_PIN        PA9
#define VBUS_SENSING_ENABLED

#define USE_UART

#define USE_UART1
#define UART1_RX_PIN            PB15
#define UART1_TX_PIN            PB14

#define USE_UART2
#define UART2_RX_PIN            PD6
#define UART2_TX_PIN            PD5

#define USE_UART3
#define UART3_RX_PIN            PB11
#define UART3_TX_PIN            PD8

#define USE_UART4
#define UART4_RX_PIN            PB8
#define UART4_TX_PIN            PA0

#define USE_UART5
#define UART5_RX_PIN            PB12
#define UART5_TX_PIN            PB13

#define USE_UART6
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

#define USE_UART7
#define UART7_RX_PIN            PA8
// UART7 TX not connected on Radix2HD

#define SERIAL_PORT_COUNT       8   // VCP + UART1-7

// *************** ADC ******************************
#define USE_ADC
#define ADC_INSTANCE            ADC1
#define ADCVREF                 3285

#define ADC_CHANNEL_1_PIN       PC0
#define ADC_CHANNEL_2_PIN       PA6
#define ADC_CHANNEL_3_PIN       PC1

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
#define MAX_PWM_OUTPUT_PORTS    10
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
