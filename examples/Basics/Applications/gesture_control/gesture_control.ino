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

// LED
uint8_t led_count = 12;

// Timing
long loopTime, startTime = 0;
long sleep_count = 0;

// IMU
float ax, ay, az;
float gx, gy, gz;

// Smoothing
float readings[6][25];
int32_t readIndex[6];
float total[6];
float average[6];

void setup() {
  // Initialize M5StickC
  M5.begin(); // Initializes Serial(115200), LCD, RTC, AXP
  // Initialize IMU
  M5.Imu.Init();
  // Initialize BT
  BT.begin("CI-N5-V");
  // Sets dislplay color and title
  setDisplay();
  // Set the smoothing array
  setSmoothArray();
}

void loop() {
  loopTime = millis();
  lowBatteryWarning();
  screenBrightness();
  setIMU();
  readBT();
  startTime = loopTime;
}

void readBT() {
  if(BT.available()) {
    Serial.println(BT.read());
  }
  delay(20);
}

void writeBT() {
  if(Serial.available()) {
    Serial.println("Sending Message ...");
    BT.write(Serial.read());
  }
}

void setDisplay(){
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(30, 0);
  M5.Lcd.println("CI-N5-V");
}

void setIMU() {
  M5.Imu.getAccelData(&ax,&ay,&az);
  M5.Imu.getGyroData(&gx,&gy,&gz);
  smooth(0, ax);
  smooth(1, ay);
  smooth(2, az);
  smooth(3, gx);
  smooth(4, gy);
  smooth(5, gz);

  Serial.printf("ax: %6.2f", average[0]); Serial.print("\t");
  Serial.printf("ay: %6.2f", average[1]); Serial.print("\t");
  Serial.printf("az: %6.2f", average[2]); Serial.print("\t");
  Serial.println();

  Serial.printf("gx: %6.2f", average[3]); Serial.print("\t");
  Serial.printf("gy: %6.2f", average[4]); Serial.print("\t");
  Serial.printf("gz: %6.2f", average[5]);
  Serial.println();
}

void setSmoothArray(){
  for (int axis = 0; axis < 6; axis++) {
    readIndex[axis] = 0;
    total[axis] = 0;
    average[axis] = 0;
    for (int i = 0; i < 25; i++){
      readings[axis][i] = 0;
    }
  }
}

void smooth(int axis, float val) {
  total[axis] -= readings[axis][readIndex[axis]];
  total[axis] += val;

  // add value to running total
  readings[axis][readIndex[axis]] = val;
  readIndex[axis]++;

  if(readIndex[axis] >= 25)
    readIndex[axis] = 0;

  // calculate the average:
  average[axis] = total[axis] / 25;
}

void screenBrightness() {
  if(digitalRead(M5_BUTTON_HOME) == LOW){
    led_count++;
    if(led_count > 12)
      led_count = 7;
    while(digitalRead(M5_BUTTON_HOME) == LOW);
    M5.Axp.ScreenBreath(led_count);
  }
}

void lowBatteryWarning(){
  if(startTime < (loopTime - 500)){
    if(M5.Axp.GetWarningLeve()){
      sleep_count++;
      if(sleep_count >= 1){
        M5.Lcd.fillScreen(WHITE);
        M5.Lcd.setCursor(0, 20, 1);
        M5.Lcd.setTextColor(RED, WHITE);
        M5.Lcd.printf("Warning: low battery");
        if(sleep_count >= 10){
          sleep_count = 0;
          M5.Axp.SetSleep();
        }
      }
    }
  }
}// ends lowBatteryWarning()
