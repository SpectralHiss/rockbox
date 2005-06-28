/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Robert E. Hak
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include <string.h>
#include "lcd.h"
#include "font.h"
#include "kernel.h"
#include "sprintf.h"
#include "rtc.h"
#include "powermgmt.h"

#include "settings.h"

#include "icons.h"

const unsigned char bitmap_icons_5x8[][5] =
{
    /* Lock */
    {0x78,0x7f,0x49,0x7f,0x78}
};

const unsigned char bitmap_icons_6x8[LastIcon][6] =
{
    { 0x00, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f }, /* Box_Filled */
    { 0x00, 0x7f, 0x41, 0x41, 0x41, 0x7f }, /* Box_Empty */
    { 0x00, 0x3e, 0x7f, 0x63, 0x7f, 0x3e }, /* Slider_Horizontal */
    { 0x60, 0x7f, 0x03, 0x33, 0x3f, 0x00 }, /* Musical note */
    { 0x7e, 0x41, 0x41, 0x42, 0x7e, 0x00 }, /* Folder */
    { 0x3e, 0x26, 0x26, 0x24, 0x3c, 0x00 }, /* Directory */
    { 0x55, 0x00, 0x55, 0x55, 0x55, 0x55 }, /* Playlist */
    { 0x39, 0x43, 0x47, 0x71, 0x61, 0x4e }, /* Repeat */
    { 0x00, 0x1c, 0x3e, 0x3e, 0x3e, 0x1c }, /* Selected */
    { 0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00 }, /* Cursor / Marker */
    { 0x58, 0x5f, 0x42, 0x50, 0x55, 0x55 }, /* WPS file */
    { 0x63, 0x7f, 0x3a, 0x7f, 0x63, 0x00 }, /* Mod or ajz file */
    { 0x60, 0x70, 0x38, 0x2c, 0x7e, 0x7e }, /* Font file */
    { 0x3e, 0x2a, 0x3e, 0x2a, 0x2a, 0x3e }, /* Language file */
    { 0x4e, 0x51, 0x51, 0x40, 0x55, 0x55 }, /* Config file */
    { 0x0a, 0x0a, 0x5f, 0x4e, 0x24, 0x18 }, /* Plugin file */
    { 0xff, 0x81, 0xaf, 0xaa, 0x8c, 0xf8 }, /* Bookmark file */
};

const unsigned char bitmap_icons_7x8[][7] =
{
    {0x08,0x1c,0x3e,0x3e,0x3e,0x14,0x14}, /* Power plug */
    {0x1c,0x14,0x3e,0x2a,0x22,0x1c,0x08}, /* USB plug */
    {0x00,0x1c,0x1c,0x3e,0x7f,0x00,0x00}, /* Speaker */
    {0x01,0x1e,0x1c,0x3e,0x7f,0x20,0x40}, /* Speaker mute */
    {0x00,0x7f,0x7f,0x3e,0x1c,0x08,0x00}, /* Play */
    {0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f}, /* Stop */
    {0x00,0x7f,0x7f,0x00,0x7f,0x7f,0x00}, /* Pause */
    {0x7f,0x3e,0x1c,0x7f,0x3e,0x1c,0x08}, /* Fast forward */
    {0x08,0x1c,0x3e,0x7f,0x1c,0x3e,0x7f}, /* Fast backward */
    {0x1c,0x3e,0x7f,0x7f,0x7f,0x3e,0x1c}, /* Record */
    {0x1c,0x3e,0x7f,0x00,0x7f,0x3e,0x1c}, /* Record pause */
    {0x44,0x4e,0x5f,0x44,0x44,0x44,0x38}, /* Repeat playmode */
    {0x44,0x4e,0x5f,0x44,0x38,0x02,0x7f}, /* Repeat-one playmode */
    {0x3e,0x41,0x51,0x41,0x45,0x41,0x3e}, /* Shuffle playmode (dice) */
    {0x04,0x0c,0x1c,0x3c,0x1c,0x0c,0x04}, /* Down-arrow */
    {0x20,0x30,0x38,0x3c,0x38,0x30,0x20}, /* Up-arrow */
};

#if CONFIG_LED == LED_VIRTUAL
/* Disk/MMC activity */
const unsigned char bitmap_icon_disk[12] = 
    {0x15,0x3f,0x7d,0x7B,0x77,0x67,0x79,0x7b,0x57,0x4f,0x47,0x7f};
#endif

#if  LCD_WIDTH == 112 || LCD_WIDTH == 128 || (defined(HAVE_REMOTE_LCD) && LCD_REMOTE_WIDTH == 128)
/* Archos Jukebox/ Ondio + Gmini LCD width / remote lcd of iriver*/

const unsigned char rockbox112x37[]={
 0x00, 0x00, 0x02, 0xff, 0x02, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa, 0xfa,
 0xf8, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc,
 0x7c, 0x7d, 0xfd, 0xfa, 0xfa, 0xf4, 0xe8, 0x90, 0x60, 0x80, 0xe0, 0x10, 0xc8,
 0xe4, 0xf2, 0xfa, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfa, 0xfa, 0xf4, 0x02, 0xfa,
 0xfa, 0xfa, 0xfa, 0x02, 0xff, 0x02, 0x00, 0x80, 0xe2, 0xfa, 0xfa, 0xfa, 0xfa,
 0x3a, 0x0e, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

 0x60, 0x90, 0x20, 0xc0, 0x00, 0xff, 0xff, 0xff, 0xff, 0x05, 0x05, 0x05, 0xf9,
 0x03, 0xff, 0xff, 0xff, 0xff, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x0f, 0x01, 0x00,
 0xff, 0x01, 0x0e, 0xf1, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x03, 0xf8, 0xff, 0xff,
 0xff, 0x0f, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0f, 0x00, 0xff,
 0xff, 0xff, 0xff, 0x80, 0xff, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0x07, 0x07, 0x04,
 0x04, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 

 0xc0, 0x38, 0x07, 0x9d, 0x60, 0xbf, 0xbf, 0xff, 0xff, 0xfc, 0xff, 0xfd, 0xfe,
 0xff, 0xff, 0x9f, 0x0f, 0x03, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x08, 0x08,
 0x3f, 0x08, 0x08, 0xff, 0x08, 0xff, 0xff, 0xff, 0xff, 0x08, 0xff, 0xff, 0xff,
 0xff, 0x08, 0x08, 0x08, 0x08, 0xfe, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0xff,
 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xf3, 0xc0, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x03, 0x82, 0x41, 0x41, 0xa1, 0xa1, 0x41, 0x41, 0x81, 0x02, 0x02, 0x04,
 0x08, 0x30, 0x08, 0x04, 0x02, 0x02, 0x81, 0x41, 0x41, 0xa1, 0xa1, 0x41, 0x41,
 0x81, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x01, 0x02, 0x0c, 0x12, 0x0d, 0x02,
 0x01, 0x01, 0xc1, 0x31, 0xc9, 0x35, 0x0b, 0x04, 

 0x01, 0x07, 0x0c, 0x09, 0x18, 0xe3, 0x1b, 0xfc, 0xff, 0x00, 0xff, 0x03, 0x1f,
 0x7f, 0xff, 0xff, 0xfc, 0xf0, 0x80, 0x0f, 0x7f, 0xff, 0xff, 0xfc, 0xe0, 0xc0,
 0xa0, 0xa0, 0xdc, 0xe3, 0xfc, 0xff, 0xff, 0x7f, 0x0f, 0x00, 0x07, 0x3f, 0xff,
 0xff, 0xfc, 0xf0, 0xe0, 0xc0, 0xff, 0xc0, 0xc0, 0xe0, 0xf0, 0xfc, 0x00, 0xff,
 0xff, 0xff, 0xff, 0x06, 0x19, 0x67, 0x9f, 0x7f, 0xff, 0xff, 0xfc, 0xf0, 0xc0,
 0x00, 0x06, 0x19, 0x20, 0x20, 0x50, 0x50, 0x29, 0x26, 0x19, 0x06, 0x00, 0x00,
 0x00, 0xc0, 0x00, 0x00, 0x00, 0x06, 0x19, 0x20, 0x20, 0x50, 0x50, 0x29, 0x26,
 0x19, 0x06, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x06, 0x00, 0x00, 0x80, 0x00, 0x00,
 0x06, 0x09, 0x36, 0xc9, 0x30, 0xc0, 0x00, 0x00, 

 0x20, 0xa0, 0x00, 0x40, 0x83, 0xec, 0x0c, 0x0f, 0x0f, 0xe8, 0xff, 0xa8, 0x08,
 0x00, 0x01, 0x0f, 0x0f, 0x0f, 0x0f, 0x0e, 0x58, 0xc9, 0x03, 0x47, 0x07, 0xef,
 0xef, 0xaf, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x08, 0x48, 0xe8, 0xe8,
 0xa9, 0x4b, 0xef, 0xef, 0xaf, 0xaf, 0xaf, 0x07, 0x47, 0x27, 0xc3, 0x00, 0x4f,
 0x8f, 0xef, 0x0f, 0x00, 0x00, 0xe8, 0xe9, 0xae, 0x19, 0x0f, 0x0f, 0x0f, 0x0f,
 0x0f, 0x0c, 0x04, 0x48, 0xc8, 0x08, 0x48, 0x68, 0x48, 0x08, 0x04, 0x24, 0xe2,
 0xe1, 0xa0, 0x61, 0x42, 0x04, 0x04, 0x88, 0x28, 0x08, 0x08, 0x28, 0xe8, 0xe8,
 0xa8, 0xc8, 0xec, 0xea, 0xa8, 0x28, 0xa8, 0x08, 0x44, 0xeb, 0x24, 0x03, 0x04,
 0x08, 0xe8, 0xe8, 0xa8, 0x09, 0x0a, 0x0d, 0x02, 

};

#endif

#if LCD_WIDTH >= 160
/* iRiver LCD width */
const unsigned char rockbox160x53[] = {
 0x00, 0x00, 0x00, 0x04, 0x04, 0xff, 0x04, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4,
 0xf4, 0xf4, 0xf4, 0xf4, 0xf4, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xfa,
 0xfa, 0xf2, 0xf4, 0xf4, 0xe8, 0xc8, 0x90, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
 0x00, 0x80, 0x40, 0x20, 0x90, 0xc8, 0xe4, 0xf4, 0xf4, 0xf2, 0xfa, 0xfa, 0xfa,
 0xf4, 0xf4, 0xf4, 0xe8, 0xc8, 0x98, 0x04, 0x04, 0xf4, 0xf4, 0xf4, 0xf4, 0xf4,
 0x04, 0xff, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe4, 0xf4, 0xf4, 0xf4, 0xf4,
 0xf4, 0x74, 0x1c, 0x06, 0x05, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0x5f, 0x5f, 0x5f, 0x5f, 0x9f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf0,
 0x00, 0x00, 0xe0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x0f, 0xcf,
 0x4f, 0x9f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe1, 0x0e, 0x70, 0x38,
 0x06, 0xf1, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x9f, 0x4f, 0x0f,
 0x1f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
 0x00, 0xff, 0x00, 0x00, 0x80, 0xe0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x8f,
 0x83, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 
 0x1c, 0x34, 0xc4, 0x08, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0x00, 0x00, 0x80, 0x80, 0xc1, 0x3e, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xff,
 0x00, 0x01, 0x1e, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xc0,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x80, 0x7c, 0x03, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
 0x00, 0xff, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
 0x80, 0x80, 0x00, 0x00, 
 0x00, 0x00, 0xf0, 0x1f, 0x0f, 0x70, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xfc, 0xff, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x03, 0x00,
 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3f,
 0x08, 0x08, 0x08, 0xff, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x08, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xd9, 0x08, 0xff, 0x08, 0x08, 0x08, 0x08, 0xff,
 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x01, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x30, 0x60, 0x10, 0x08, 0x04,
 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06,
 0x1c, 0x32, 0x1d, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x30, 0x8c,
 0x67, 0x19, 0x06, 0x01, 
 0x00, 0x1f, 0x7f, 0x60, 0xc4, 0xc2, 0x83, 0x30, 0x0e, 0x9c, 0xc1, 0xff, 0xff,
 0x03, 0xff, 0x03, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xc0, 0x00,
 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0xc0, 0x3c, 0x83, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x03,
 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x1f, 0x60, 0x80, 0x00, 0xff,
 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
 0x0f, 0x19, 0xe3, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0xfc, 0x86, 0x01, 0x01, 0x00, 0x00, 0x02, 0x82, 0x85,
 0x79, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x78, 0x86, 0x03, 0x01, 0x00, 0x00, 0x02, 0x02, 0x04, 0xc9, 0x33,
 0xce, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x20, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xec, 0x07, 0x71, 0x8c, 0x03, 0x00,
 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x70, 0x0f, 0xff, 0xff,
 0x00, 0xff, 0x00, 0x00, 0x00, 0x03, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff,
 0xf8, 0xc0, 0x03, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xfa,
 0xf9, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x03, 0x00, 0x00, 0x00,
 0x00, 0x07, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf9, 0xf9, 0xff,
 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
 0x00, 0x00, 0x00, 0x07, 0x38, 0xc3, 0x1f, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x04, 0x05, 0x05, 0x04, 0x04,
 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x30, 0x18, 0x20, 0xc0, 0x80,
 0x00, 0x00, 0x00, 0x01, 0x02, 0x06, 0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x03,
 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
 0x60, 0xb0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x19, 0x72, 0xcc,
 0x10, 0x60, 0x80, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x06, 0x07, 0x07, 0x07,
 0x04, 0x1f, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x07,
 0x07, 0x07, 0x07, 0x1c, 0x04, 0x04, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x0f,
 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x08, 0x08, 0x08, 0x08, 0x09, 0x0b, 0x0b, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
 0x0f, 0x07, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07,
 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x1c, 0x07, 0x07, 0x04, 0x04, 0x04,
 0x04, 0x04, 0x04, 0x04, 0x06, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x01, 0x03, 0x02, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
 0x06, 0x06, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x06, 0x01,
 0x06, 0x01, 0x00, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
 0x07, 0x06, 0x00, 0x06,
};

#endif

/*
 * Print battery icon to status bar
 */
void statusbar_icon_battery(int percent)
{
    int i;
    int fill;
    char buffer[5];
    unsigned int width, height;

    /* fill battery */
    fill=percent;
    if (fill < 0)
        fill = 0;
    if (fill > 100)
        fill = 100;

#ifdef SIMULATOR
    if (global_settings.battery_display && (percent > -1)) {
#else
#ifdef HAVE_CHARGE_CTRL /* Recorder */
    /* show graphical animation when charging instead of numbers */
    if ((global_settings.battery_display) &&
        (charge_state != 1) &&
        (percent > -1)) {
#else /* FM */
    if (global_settings.battery_display && (percent > -1)) {
#endif /* HAVE_CHARGE_CTRL */
#endif
        /* Numeric display */
        snprintf(buffer, sizeof(buffer), "%3d", fill);
        lcd_setfont(FONT_SYSFIXED);
        lcd_getstringsize(buffer, &width, &height);
        if (height <= STATUSBAR_HEIGHT)
            lcd_putsxy(ICON_BATTERY_X_POS + ICON_BATTERY_WIDTH / 2 -
                       width/2, STATUSBAR_Y_POS, buffer);
        lcd_setfont(FONT_UI);

    }
    else {
        /* draw battery */
        lcd_drawrect(ICON_BATTERY_X_POS, STATUSBAR_Y_POS, 17, 7);
        for (i=2; i < 5; i++)
            lcd_drawpixel(ICON_BATTERY_X_POS + 17, STATUSBAR_Y_POS + i);

        fill = fill * 15 / 100;

        lcd_fillrect(ICON_BATTERY_X_POS + 1, STATUSBAR_Y_POS + 1, fill, 5);
    }

    if (percent == -1) {
        lcd_setfont(FONT_SYSFIXED);
        lcd_putsxy(ICON_BATTERY_X_POS + ICON_BATTERY_WIDTH / 2 - 4,
                   STATUSBAR_Y_POS, "?");
        lcd_setfont(FONT_UI);
    }
}

/*
 * Print volume gauge to status bar
 */
bool statusbar_icon_volume(int percent)
{
    int i,j;
    int volume;
    int vol;
    int step=0;
    char buffer[4];
    unsigned int width, height;
    bool needs_redraw = false;
    int type = global_settings.volume_type;
#if defined(LOADABLE_FONTS)
    unsigned char *font;
#endif
    static long switch_tick;
    static int last_volume = -1; /* -1 means "first update ever" */

    volume = percent;
    if (volume < 0)
        volume = 0;
    if (volume > 100)
        volume = 100;

    if (volume==0) {
        lcd_bitmap(bitmap_icons_7x8[Icon_Mute], 
                   ICON_VOLUME_X_POS + ICON_VOLUME_WIDTH / 2 - 4,
                   STATUSBAR_Y_POS, 7, STATUSBAR_HEIGHT);
    }
    else {
        /* We want to redraw the icon later on */
        if (last_volume != volume && last_volume >= 0) {
            switch_tick = current_tick + HZ;
        }

        /* If the timeout hasn't yet been reached, we show it numerically
           and tell the caller that we want to be called again */
        if(TIME_BEFORE(current_tick,switch_tick)) {
            type = 1;
            needs_redraw = true;
        }
        
        /* display volume level numerical? */
        if (type)
        {
            snprintf(buffer, sizeof(buffer), "%2d", percent);
            lcd_setfont(FONT_SYSFIXED);
            lcd_getstringsize(buffer, &width, &height);
            if (height <= STATUSBAR_HEIGHT)
                lcd_putsxy(ICON_VOLUME_X_POS + ICON_VOLUME_WIDTH / 2 -
                           width/2, STATUSBAR_Y_POS, buffer);
            lcd_setfont(FONT_UI);
        } else { 
            /* display volume bar */
            vol = volume * 14 / 100;
            for(i=0; i < vol; i++) {
                if(i%2 == 0)
                    step++;
                for(j=1; j <= step; j++)
                    lcd_drawpixel(ICON_VOLUME_X_POS + i, 
                                  STATUSBAR_Y_POS + 7 - j);
            }
        }
    }
    last_volume = volume;

    return needs_redraw;
}

/*
 * Print play state to status bar
 */
void statusbar_icon_play_state(int state)
{
    lcd_bitmap(bitmap_icons_7x8[state], ICON_PLAY_STATE_X_POS, STATUSBAR_Y_POS,
               ICON_PLAY_STATE_WIDTH, STATUSBAR_HEIGHT);
}

/*
 * Print play mode to status bar
 */
void statusbar_icon_play_mode(int mode)
{
    lcd_bitmap(bitmap_icons_7x8[mode], ICON_PLAY_MODE_X_POS, STATUSBAR_Y_POS,
               ICON_PLAY_MODE_WIDTH, STATUSBAR_HEIGHT);
}

/*
 * Print shuffle mode to status bar
 */
void statusbar_icon_shuffle(void)
{
    lcd_bitmap(bitmap_icons_7x8[Icon_Shuffle], ICON_SHUFFLE_X_POS, 
               STATUSBAR_Y_POS, ICON_SHUFFLE_WIDTH, STATUSBAR_HEIGHT);
}

/*
 * Print lock when keys are locked
 */
void statusbar_icon_lock(void)
{
    lcd_bitmap(bitmap_icons_5x8[Icon_Lock], LOCK_X_POS, 
               STATUSBAR_Y_POS, 5, 8);
}

#if CONFIG_LED == LED_VIRTUAL
/*
 * no real LED: disk activity in status bar
 */
void statusbar_led(void)
{
    lcd_bitmap(bitmap_icon_disk, ICON_DISK_X_POS, 
               STATUSBAR_Y_POS, ICON_DISK_WIDTH, STATUSBAR_HEIGHT);
}
#endif

#ifdef HAVE_RTC
/*
 * Print time to status bar
 */
void statusbar_time(int hour, int minute)
{
    unsigned char buffer[6];
    unsigned int width, height;

    if ( hour >= 0 && 
         hour <= 23 &&
         minute >= 0 && 
         minute <= 59 ) {
        if ( global_settings.timeformat ) { /* 12 hour clock */
            hour %= 12;
            if ( hour == 0 ) {
                hour +=12;
            }
        }
        snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
    }
    else {
        strncpy(buffer, "--:--", sizeof buffer);
    }

    lcd_setfont(FONT_SYSFIXED);
    lcd_getstringsize(buffer, &width, &height);
    if (height <= STATUSBAR_HEIGHT)
        lcd_putsxy(TIME_X_END - width, STATUSBAR_Y_POS, buffer);
    lcd_setfont(FONT_UI);
}
#endif
