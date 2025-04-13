#include <Arduino.h>

#include "draw.h"
#include "gif.h"

AnimatedGIF gif;

void setup() {
  Serial.begin(115200);
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
