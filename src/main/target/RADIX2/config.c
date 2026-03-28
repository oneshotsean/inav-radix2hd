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
    // PINIO1 is the VTX pit switch on the RADIX 2 (analog variant).
    // Map it to USER1 box so it can be toggled via a flight mode switch.
    // When active: VTX power is cut (pit mode / safe ground operation).
    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;
}

#endif
