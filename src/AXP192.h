#ifndef __AXP192_H__
#define __AXP192_H__
#pragma once
/**
 * @class AXP192
 * @brief M5StickC library
 * @file AXP192.h
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 * 
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#include <Wire.h>
#include <Arduino.h>

#define SLEEP_MSEC(us) (((uint64_t)us) * 1000L)
#define SLEEP_SEC(us)  (((uint64_t)us) * 1000000L)
#define SLEEP_MIN(us)  (((uint64_t)us) * 60L * 1000000L)
#define SLEEP_HR(us)   (((uint64_t)us) * 60L * 60L * 1000000L)


class AXP192 {
  public:
    AXP192();
    void  begin(void);
    void  ScreenBreath(uint8_t brightness);
    
    void  EnableCoulombcounter(void);
    void  DisableCoulombcounter(void);
    void  StopCoulombcounter(void);
    void  ClearCoulombcounter(void);
    
    uint32_t GetCoulombchargeData(void);
    uint32_t GetCoulombdischargeData(void);
    float GetCoulombData(void);

    uint16_t GetVbatData(void);

    uint16_t GetIchargeData(void);
    uint16_t GetIdischargeData(void);

    uint16_t GetTempData(void);

    uint32_t GetPowerbatData(void);

    uint16_t GetVinData(void);
    uint16_t GetIinData(void);

    uint16_t GetVusbinData(void);
    uint16_t GetIusbinData(void);

    uint16_t GetVapsData(void);
    uint8_t GetBtnPress(void);
    
    void SetSleep(void);

    void DeepSleep(uint64_t time_in_us = 0);
    void LightSleep(uint64_t time_in_us = 0);
    uint8_t GetWarningLeve(void);
}; 

#endif
