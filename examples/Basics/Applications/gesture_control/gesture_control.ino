/**
 * CI-N5-V
 * @author: Hugo J. Marquez
 * @description: Gesture Control with IMU, AXP, BT modules
 *
 */

#include <M5StickC.h>
#include <BluetoothSerial.h>

// BT
BluetoothSerial BT;
// Timing
long loopTime, startTime = 0;

void setup() {
  // Initialize serial monitor
  //Serial.begin(9600);
  // Initialize M5StickC
  M5.begin(); // Initializes Serial(115200), LCD, RTC, AXP
  // Button
  pinMode(M5_BUTTON_HOME, INPUT);
  // Initialize IMU
  M5.Imu.Init();
  // Initialize BT
  BT.begin("CI-N5-V");
  // Sets dislplay color and title
  setDisplay();
}

void loop() {
  loopTime = millis();
  //lowBatteryWarning();
  //screenBrightness();
  trainMotion();
  startTime = loopTime;
}
