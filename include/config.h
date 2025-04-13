#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino_DataBus.h>
#include <cstdint>
#include <pins_arduino.h>

static const int8_t BUS_DC = 2;
static const int8_t BUS_CS = 15;
static const int8_t BUS_SCK = SCK;
static const int8_t BUS_MOSI = MOSI;
static const int8_t BUS_MISO = GFX_NOT_DEFINED;
static const int8_t GFX_RST = 4;

static const uint8_t GFX_ROTATION = 0;
static const int16_t GFX_WIDTH = 135;
static const int16_t GFX_HEIGHT = 240;
static const uint8_t GFX_COL_OFFSET1 = 52;
static const uint8_t GFX_ROW_OFFSET1 = 40;
static const uint8_t GFX_COL_OFFSET2 = 53;
static const uint8_t GFX_ROW_OFFSET2 = 40;

#endif // _CONFIG_H_
