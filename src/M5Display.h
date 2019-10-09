#ifndef _M5DISPLAY_H_
#define _M5DISPLAY_H_
#pragma once

/**
 * @class M5Display
 * @brief M5StickC library
 * @file M5Display.h
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 * 
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#include <Arduino.h>
#include <FS.h>
#include <SPI.h>

#include "utility/In_eSPI.h"
#include "utility/Sprite.h"
#include "Fonts/HZK16.h"
#include "Fonts/ASC16.h"

typedef enum {
  JPEG_DIV_NONE,
  JPEG_DIV_2,
  JPEG_DIV_4,
  JPEG_DIV_8,
  JPEG_DIV_MAX
} jpeg_div_t;


typedef enum {
  DontUsedHzk16,
  InternalHzk16,
  ExternalHzk16
} Hzk16Types;

class M5Display : public TFT_eSPI {
  private:
    void writeHzkAsc(const char c);
    void writeHzkGbk(const char *c);
    bool initHzk16(boolean use, const char *HZK16Path, const char *ASC16Path);
    inline bool isHzk16Used(){return hzk16Used;}
    bool hzk16Used,istransparent, highlighted;
    uint8_t hzkBufCount;
    uint8_t *pAscCharMatrix, *pGbkCharMatrix; 
    uint16_t highlightcolor, ascCharWidth, ascCharHeigth, gbkCharWidth, gbkCharHeight;
    // Use of HZK16 and ASC16 font. 
    Hzk16Types  hzk16Type;
    // Font file
    File Asc16File, Hzk16File, *pAsc16File, *pHzk16File;
    // If set, 'wrap' text at right edge of display
    bool  textwrap;

  public:
    M5Display();
    void begin();
    void sleep();
    void setBrightness(uint8_t brightness);
    void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint16_t *data);
    void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint8_t *data);
    void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, uint16_t *data);
    void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, uint8_t *data);
    void drawBitmap(int16_t x0, int16_t y0, int16_t w, int16_t h, const uint16_t *data, uint16_t transparent);
    
    void loadHzk16(Hzk16Types hzkTypes = InternalHzk16,const char* HZK16Path = "/HZK16", const char* ASC16Path = "/ASC16");
    void setTextWrap(boolean wrap);

    void writeHzk(char* c);
    // Highlight the text (Once set to be true, the text background will not be transparent any more)
    inline void highlight(bool isHighlight) { highlighted = isHighlight; }
    // Set highlight color
    inline void setHighlightColor(uint16_t color) { highlightcolor = color; istransparent = false; }
    void qrcode(const char *string, uint16_t x = 5, uint16_t y = 45, uint8_t width = 70, uint8_t version = 7);
    void qrcode(const String &string, uint16_t x = 5, uint16_t y = 45, uint8_t width = 70, uint8_t version = 7);
};
#endif
