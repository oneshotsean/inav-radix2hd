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
// Verified against BrainFPV/inav brainfpv branch target.c
//
// S1-S8: primary motor outputs
// S9/S10: extended outputs on UART2 TX/RX pads — disable UART2 to use
// PPM: PB14 (TIM12 CH1) — enable in configurator to use PPM input
timerHardware_t timerHardware[] = {
    DEF_TIM(TIM2,  CH1, PA0,   TIM_USE_OUTPUT_AUTO, 0, 0),  // S1
    DEF_TIM(TIM3,  CH2, PB5,   TIM_USE_OUTPUT_AUTO, 0, 1),  // S2
    DEF_TIM(TIM4,  CH1, PD12,  TIM_USE_OUTPUT_AUTO, 0, 2),  // S3
    DEF_TIM(TIM4,  CH2, PD13,  TIM_USE_OUTPUT_AUTO, 0, 3),  // S4

    DEF_TIM(TIM8,  CH4, PC9,   TIM_USE_OUTPUT_AUTO, 0, 4),  // S5
    DEF_TIM(TIM8,  CH3, PC8,   TIM_USE_OUTPUT_AUTO, 0, 5),  // S6
    DEF_TIM(TIM1,  CH3, PE13,  TIM_USE_OUTPUT_AUTO, 0, 6),  // S7
    DEF_TIM(TIM1,  CH2, PE11,  TIM_USE_OUTPUT_AUTO, 0, 7),  // S8

    // Extended outputs on UART2 pads — requires UART2 disabled
    DEF_TIM(TIM15, CH1, PA2,   TIM_USE_OUTPUT_AUTO, 0, 0),  // S9  (TX2)
    DEF_TIM(TIM15, CH2, PA3,   TIM_USE_OUTPUT_AUTO, 0, 0),  // S10 (RX2)

    // PPM input on PB14 (TIM12 CH1)
    // DEF_TIM(TIM12, CH1, PB14, TIM_USE_PPM, 0, 0),  // PPM In
};

const int timerHardwareCount = sizeof(timerHardware) / sizeof(timerHardware[0]);
