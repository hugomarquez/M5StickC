#ifndef _M5STICKC_H_
#define _M5STICKC_H_
#pragma once

/**
 * @class M5StickC
 * @brief M5StickC library
 * @file M5StickC.h
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 * 
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#if defined(ESP32)

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "M5Display.h"
#include "AXP192.h"
#include "RTC.h"
#include "IMU.h"

#include "utility/Config.h"
#include "utility/SH200Q.h"
#include "utility/MPU6886.h"
#include "utility/Button.h"


class M5StickC {
  private:
    bool _isInit;
  public:
    M5Display Lcd = M5Display();
    AXP192 Axp = AXP192();
    RTC  Rtc;
    IMU Imu;
    MPU6886 Mpu6886;
    SH200Q Sh200Q;

    #define DEBOUNCE_MS 10
    Button btnA = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
    Button btnB = Button(BUTTON_B_PIN, true, DEBOUNCE_MS);

    // Constructor
    M5StickC();
	  void begin(bool display=true, bool power=true, bool serial=true);
    void update();
};

extern M5StickC M5;
#else
#error “This library only supports boards with ESP32 processor.”	
#endif
#endif