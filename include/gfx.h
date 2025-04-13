#ifndef _GFX_H_
#define _GFX_H_

#include "config.h"
#include <Arduino_GFX_Library.h>

Arduino_DataBus *bus =
    new Arduino_ESP32SPI(BUS_DC, BUS_CS, BUS_SCK, BUS_MOSI, BUS_MISO);
Arduino_GFX *gfx = new Arduino_ST7789(
    bus, GFX_RST, GFX_ROTATION, true, GFX_WIDTH, GFX_HEIGHT, GFX_COL_OFFSET1,
    GFX_ROW_OFFSET1, GFX_COL_OFFSET2, GFX_ROW_OFFSET2);

#endif // _GFX_H_
