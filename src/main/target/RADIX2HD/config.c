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
    // PINIO1 is the HD video regulator enable switch.
    // Map it to USER1 box so it can be toggled via flight modes.
    pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;

    // UART1 defaults to MSP OSD (for HD OSD systems such as DJI, Walksnail, HDZero)
    serialConfigMutable()->portConfigs[findSerialPortIndexByIdentifier(SERIAL_PORT_USART1)].functionMask = FUNCTION_MSP_OSD;
}

#endif
