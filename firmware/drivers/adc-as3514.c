/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2006 by Barry Wardell
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include "adc.h"
#include "kernel.h"
#include "ascodec.h"
#include "as3514.h"

/* Read 10-bit channel data */
unsigned short adc_read(int channel)
{
    unsigned char buf[2];

    ascodec_lock();

    /* Select channel */
    ascodec_write(AS3514_ADC_0, (channel << 4));

    ascodec_readbytes(AS3514_ADC_0, 2, buf);

    ascodec_unlock();

    return (((buf[0] & 0x3) << 8) | buf[1]);
}

void adc_init(void)
{
}
