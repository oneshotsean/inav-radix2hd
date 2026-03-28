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

#include <stdint.h>

#include "platform.h"
#include "drivers/io.h"
#include "drivers/pwm_mapping.h"
#include "drivers/timer.h"

// BrainFPV RADIX 2 timer map
// Pin constraints vs RADIX2HD:
//   PA2/PA3 = UART2 TX/RX (can't use TIM2_CH3/CH4 on those pins)
//   PA15    = SPI3_NSS (can't use TIM2_CH1)
//   PB3     = SPI3_SCK (can't use TIM2_CH2)
//   PB6     = UART1_TX (can't use TIM4_CH1)
//   PA8     = FPGA_CLOCK reference (UART7_RX equivalent — use cautiously)
//   PD8     = UART3_TX, PD5 = UART2_TX (restrict PD timer channels used)
//
// NOTE: Exact motor output pin assignments not published in BrainFPV's
// target.c. These assignments use available H750 timer channels that
// avoid all known RADIX 2 peripheral pin conflicts. Verify against
// hardware before flying.
timerHardware_t timerHardware[] = {
    DEF_TIM(TIM1,  CH2, PE11,  TIM_USE_OUTPUT_AUTO, 0, 0),  // S1
    DEF_TIM(TIM1,  CH3, PE13,  TIM_USE_OUTPUT_AUTO, 0, 1),  // S2
    DEF_TIM(TIM1,  CH1, PA10,  TIM_USE_OUTPUT_AUTO, 0, 2),  // S3
    DEF_TIM(TIM2,  CH3, PB10,  TIM_USE_OUTPUT_AUTO, 0, 3),  // S4

    DEF_TIM(TIM3,  CH2, PB5,   TIM_USE_OUTPUT_AUTO, 0, 4),  // S5
    DEF_TIM(TIM3,  CH4, PB1,   TIM_USE_OUTPUT_AUTO, 0, 5),  // S6
    DEF_TIM(TIM4,  CH2, PD13,  TIM_USE_OUTPUT_AUTO, 0, 6),  // S7
    DEF_TIM(TIM4,  CH4, PD15,  TIM_USE_OUTPUT_AUTO, 0, 7),  // S8
};

const int timerHardwareCount = sizeof(timerHardware) / sizeof(timerHardware[0]);
