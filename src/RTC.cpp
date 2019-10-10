/**
 * @class RTC
 * @brief M5StickC library
 * @file RTC.cpp
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 * 
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#include "RTC.h"

RTC::RTC(){}

void RTC::begin(void) {
  Wire1.begin(21,22);
}

void RTC::GetBm8563Time(void) {
  Wire1.beginTransmission(0x51);
  Wire1.write(0x02);
  Wire1.endTransmission();
  Wire1.requestFrom(0x51,7); 
  
  while(Wire1.available()){
    trdata[0] = Wire1.read();
    trdata[1] = Wire1.read();
    trdata[2] = Wire1.read();
    trdata[3] = Wire1.read();
    trdata[4] = Wire1.read();
    trdata[5] = Wire1.read();
    trdata[6] = Wire1.read();
  }

  DataMask();
  Bcd2asc();
  Str2Time();
}


void RTC::Str2Time(void){
  Second = (asc[0] - 0x30) * 10 + asc[1] - 0x30;
  Minute = (asc[2] - 0x30) * 10 + asc[3] - 0x30;
  Hour = (asc[4] - 0x30) * 10 + asc[5] - 0x30;
}

void RTC::DataMask(){
  trdata[0] = trdata[0]&0x7f;    // Second
  trdata[1] = trdata[1]&0x7f;    // Minute
  trdata[2] = trdata[2]&0x3f;    // Hour
  
  trdata[3] = trdata[3]&0x3f;    // Day
  trdata[4] = trdata[4]&0x07;    // Week
  trdata[5] = trdata[5]&0x1f;    // Month
  trdata[6] = trdata[6]&0xff;    // Year
}

/**
 * Convert bcd code to asc code for LCD display
 **/
void RTC::Bcd2asc(void) {
  uint8_t i,j;
  for (j=0,i=0; i<7; i++){
    // The format is: second minute hour day month week year
    asc[j++] =(trdata[i]&0xf0)>>4|0x30;
    asc[j++] =(trdata[i]&0x0f)|0x30;
  }
}


uint8_t RTC::Bcd2ToByte(uint8_t Value) {
  uint8_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
}

uint8_t RTC::ByteToBcd2(uint8_t Value) {
  uint8_t bcdhigh = 0;
  while (Value >= 10) {
    bcdhigh++;
    Value -= 10;
  }
  return  ((uint8_t)(bcdhigh << 4) | Value);
}


void RTC::GetTime(RTC::Time* time) { 
  uint8_t buf[3] = {0};

  Wire1.beginTransmission(0x51);
  Wire1.write(0x02);
  Wire1.endTransmission();
  Wire1.requestFrom(0x51,3);

  while(Wire1.available()) {
    buf[0] = Wire1.read();
    buf[1] = Wire1.read();
    buf[2] = Wire1.read();
  }

  time -> Seconds  = Bcd2ToByte(buf[0]&0x7f);
  time -> Minutes  = Bcd2ToByte(buf[1]&0x7f);
  time -> Hours    = Bcd2ToByte(buf[2]&0x3f);
}

void RTC::SetTime(RTC::Time* time){
  if(time == NULL)
    return;

  Wire1.beginTransmission(0x51);
  Wire1.write(0x02);
  Wire1.write(ByteToBcd2(time->Seconds)); 
  Wire1.write(ByteToBcd2(time->Minutes)); 
  Wire1.write(ByteToBcd2(time->Hours)); 
  Wire1.endTransmission();
}



void RTC::GetData(RTC::Date* date){
  uint8_t buf[4] = {0};

  Wire1.beginTransmission(0x51);
  Wire1.write(0x05);
  Wire1.endTransmission();
  Wire1.requestFrom(0x51,4); 

  while(Wire1.available()) {
    buf[0] = Wire1.read();
    buf[1] = Wire1.read();
    buf[2] = Wire1.read();
    buf[3] = Wire1.read();
  }

  date -> Date    = Bcd2ToByte(buf[0]&0x3f);
  date -> WeekDay = Bcd2ToByte(buf[1]&0x07);
  date -> Month   = Bcd2ToByte(buf[2]&0x1f);

  if(buf[2]&0x80){
    date -> Year = 1900 + Bcd2ToByte(buf[3]&0xff);
  } else {
    date -> Year = 2000  + Bcd2ToByte(buf[3]&0xff);
  }
}


void RTC::SetData(RTC::Date* date){
  if(date == NULL)
    return;
  
  Wire1.beginTransmission(0x51);
  Wire1.write(0x05);
  Wire1.write(ByteToBcd2(date->Date)); 
  Wire1.write(ByteToBcd2(date->WeekDay)); 
  
  if(date->Year < 2000){
    Wire1.write(ByteToBcd2(date->Month) | 0x80); 
    Wire1.write(ByteToBcd2((uint8_t)(date->Year % 100))); 
  }else {
    Wire1.write(ByteToBcd2(date->Month) | 0x00); 
    Wire1.write(ByteToBcd2((uint8_t)(date->Year %100))); 
  }  
  Wire1.endTransmission();
}
