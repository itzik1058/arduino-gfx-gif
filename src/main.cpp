#include <Arduino.h>

#include "gif.h"
#include <AnimatedGIF.h>
#include <Arduino_GFX_Library.h>

Arduino_DataBus *bus = new Arduino_ESP32SPI(2, 15, 18, 23, GFX_NOT_DEFINED);
Arduino_GFX *gfx =
    new Arduino_ST7789(bus, 4, 0, true, 135, 240, 52, 40, 53, 40);

AnimatedGIF gif;

typedef struct {
  const uint8_t *pData;
  int32_t iSize;
  int32_t iPos;
} MEMINFO;

MEMINFO gifMemInfo;
void GIFDraw(GIFDRAW *pDraw);

void setup() {
  Serial.begin(115200);
  Serial.println("Animated GIF (Memory Array) + Arduino_GFX Example");

  if (!gfx->begin()) {
    Serial.println("gfx->begin() failed!");
    while (1)
      ;
  }
  gfx->fillScreen(BLACK);

  gif.begin(BIG_ENDIAN_PIXELS);
}

void loop() {
  if (gif.open((uint8_t *)GIF_IMAGE, sizeof(GIF_IMAGE), GIFDraw)) {
    Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n",
                  gif.getCanvasWidth(), gif.getCanvasHeight());
    GIFINFO gi;
    if (gif.getInfo(&gi)) {
      Serial.printf("frame count: %d\n", gi.iFrameCount);
      Serial.printf("duration: %d ms\n", gi.iDuration);
      Serial.printf("max delay: %d ms\n", gi.iMaxDelay);
      Serial.printf("min delay: %d ms\n", gi.iMinDelay);
    }
    unsigned long start_ms = millis();
    int iFrames = 0;
    while (gif.playFrame(true, NULL)) {
      iFrames++;
    };
    Serial.printf("total decode time for %d frames = %lu ms\n", iFrames,
                  millis() - start_ms);
    gif.close();
  } else {
    Serial.printf("Error opening file = %d\n", gif.getLastError());
    while (1)
      ;
  }
}

void GIFDraw(GIFDRAW *pDraw) {
  uint8_t *s;
  uint16_t *d, *usPalette, usTemp[320];
  int x, y, iWidth;

  iWidth = pDraw->iWidth;
  if (iWidth + pDraw->iX > gfx->width()) {
    iWidth = gfx->width() - pDraw->iX;
  }
  usPalette = pDraw->pPalette;
  y = pDraw->iY + pDraw->y; // current line
  if (y >= gfx->height() || pDraw->iX >= gfx->width() || iWidth < 1) {
    return;
  }
  s = pDraw->pPixels;
  if (pDraw->ucDisposalMethod == 2) // restore to background color
  {
    for (x = 0; x < iWidth; x++) {
      if (s[x] == pDraw->ucTransparent) {
        s[x] = pDraw->ucBackground;
      }
    }
    pDraw->ucHasTransparency = 0;
  }

  // Apply the new pixels to the main image
  if (pDraw->ucHasTransparency) // if transparency used
  {
    uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
    int x, iCount;
    pEnd = s + iWidth;
    x = 0;
    iCount = 0; // count non-transparent pixels
    while (x < iWidth) {
      c = ucTransparent - 1;
      d = usTemp;
      while (c != ucTransparent && s < pEnd) {
        c = *s++;
        if (c == ucTransparent) // done, stop
        {
          s--; // back up to treat it like transparent
        } else // opaque
        {
          *d++ = usPalette[c];
          iCount++;
        }
      } // while looking for opaque pixels
      if (iCount) // any opaque pixels?
      {
        gfx->draw16bitBeRGBBitmap(pDraw->iX + x, y, usTemp, iCount, 1);
        x += iCount;
        iCount = 0;
      }
      // no, look for a run of transparent pixels
      c = ucTransparent;
      while (c == ucTransparent && s < pEnd) {
        c = *s++;
        if (c == ucTransparent) {
          iCount++;
        } else {
          s--;
        }
      }
      if (iCount) {
        x += iCount; // skip these
        iCount = 0;
      }
    }
  } else {
    s = pDraw->pPixels;
    // Translate the 8-bit pixels through the RGB565 palette (already byte
    // reversed)
    for (x = 0; x < iWidth; x++) {
      usTemp[x] = usPalette[*s++];
    }
    gfx->draw16bitBeRGBBitmap(pDraw->iX, y, usTemp, iWidth, 1);
  }
}
