/**
 * CI-N5-V
 * @author: Hugo J. Marquez
 * @description: Gesture Control Training module
 *
 */

 void trainMotion() {
   byte vector[128];
   /* Wait until button is pressed */
   while (digitalRead(M5_BUTTON_HOME) == HIGH);

   if(digitalRead(M5_BUTTON_HOME) == LOW) {
     Serial.println("GO!");
     delay(500);
     Serial.println("NOW!");
     delay(100);
     readIMU(vector);
   }
   printVector(vector);
 }

 void printVector(byte vector[]) {
   unsigned int count = 1;
   for (unsigned int i = 0; (i + 3) < 128;) {
     Serial.printf("%i", count); Serial.printf("\t");
     Serial.printf("x: %i", vector[i]); Serial.print("\t");
     Serial.printf("y: %i", vector[i+1]); Serial.print("\t");
     Serial.printf("z: %i", vector[i+2]); Serial.print("\t");
     Serial.println();
     i += 3;
     count++;
   }
 }
