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

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"

#ifdef USE_TARGET_CONFIG

#include "fc/fc_msp_box.h"
#include "io/piniobox.h"
#include "io/serial.h"

void targetConfiguration(void)
{
    // PINIO1 (PD15) is the VTX pit switch on the RADIX 2 analog variant.
    // Map it to USER1 so the pilot can cut VTX power via a flight mode switch.
    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;

    // PINIO2 (PC15) is the video input selector (dual camera switching).
    // Map it to USER2 so the pilot can switch cameras via a flight mode switch.
    pinioBoxConfigMutable()->permanentId[1] = BOX_PERMANENT_ID_USER2;
}

#endif
