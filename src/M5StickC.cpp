/**
 * @class M5StickC
 * @brief M5StickC library
 * @file M5StickC.cpp
 * @author M5Stack
 * @version v0.1.0
 * @date 2019/09/08
 *
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * Copyright (c) M5Stack. All rights reserved.
 **/

#include "M5StickC.h"

M5StickC::M5StickC():_isInit(0) {}

void M5StickC::begin(bool display, bool power, bool serial){
	if (_isInit) return;
	else _isInit = true;

	if (serial) {
		Serial.begin(115200);
		Serial.flush();
		delay(50);
		Serial.print("M5StickC initializing...");
	}

	if (power) {
		Axp.begin();
	}

	if (display) {
		Lcd.begin();
	}

	if (serial) {
		Serial.println("OK");
	}
	Rtc.begin();
}

void M5StickC::update() {
	M5.btnA.read();
	M5.btnB.read();
}

M5StickC M5;
