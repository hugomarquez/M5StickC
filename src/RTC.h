#ifndef __RTC_H__
#define __RTC_H__
#pragma once
/**
 * @class RTC
 * @brief M5StickC library
 * @file RTC.h
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 * 
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#include <Wire.h>

class RTC {
  private:
    void Bcd2asc(void);
    void DataMask();
    void Str2Time(void);
    uint8_t Bcd2ToByte(uint8_t Value);
    uint8_t ByteToBcd2(uint8_t Value);
    
    // 定义数组用来存储读取的时间数据
    // Google Translate: Define an array to store the read time data
    uint8_t trdata[7];
    
    // 定义数组用来存储转换的 asc 码时间数据
    // Google Translate: Define an array to store the converted asc code time data
    //uint8_t asc[14]; 
  public:
    typedef struct {
      uint8_t Hours;
      uint8_t Minutes;
      uint8_t Seconds;
    } Time;
    
    typedef struct {
      uint8_t WeekDay;
      uint8_t Month;
      uint8_t Date;
      uint16_t Year;
    } Date;

    uint8_t Second;
    uint8_t Minute;
    uint8_t Hour;
    uint8_t Week;
    uint8_t Day;
    uint8_t Month;
    uint8_t  Year;
    uint8_t DateString[9];
    uint8_t TimeString[9];
    uint8_t asc[14];

    RTC();

    void begin(void);
    void GetBm8563Time(void);

    void SetTime(Time* time);
    void SetData(Date* date);

    void GetTime(Time* time);
    void GetData(Date* date); 
};

#endif
