/**
 * CI-N5-V
 * @author: Hugo J. Marquez
 * @description: Gesture Control IMU module
 *
 */

 // IMU
 float ax, ay, az;

 // Smoothing
 float readings[3][25];
 int32_t readIndex[3];
 float total[3];
 float average[3];

 void setIMU() {
   M5.Imu.getAccelData(&ax,&ay,&az);

   Serial.printf("ax: %6.2f", ax); Serial.print("\t");
   Serial.printf("ay: %6.2f", ay); Serial.print("\t");
   Serial.printf("az: %6.2f", az); Serial.print("\t");
 }

 void setSmoothArray(){
   for (int axis = 0; axis < 3; axis++) {
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
