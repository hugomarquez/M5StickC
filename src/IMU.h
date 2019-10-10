#ifndef __IMU_H__
#define __IMU_H__
#pragma once
/**
 * @class IMU
 * @brief M5StickC library
 * @file IMU.h
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 * 
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#include <Wire.h>
#include <Arduino.h>
#include "utility/MahonyAHRS.h"

class IMU {
  public:
    // It uses the IMU class as scope, so just calling it Type
    enum Type {
      IMU_UNKNOWN = 0, IMU_SH200Q, IMU_MPU6886
    };

    Type imuType;
    float aRes, gRes;

    IMU();
    int Init(void);

    void getGres();
    void getAres();

    void getAccelAdc(int16_t *ax, int16_t *ay, int16_t *az);
    void getGyroAdc(int16_t *gx, int16_t *gy, int16_t *gz);
    void getTempAdc(int16_t *t);

    void getAccelData(float *ax, float *ay, float *az);
    void getGyroData(float *gx, float *gy, float *gz);
    void getTempData(float *t);

    void getAhrsData(float *pitch,float *roll,float *yaw);
};

#endif
