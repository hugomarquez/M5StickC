/**
 * CI-N5-V
 * @author: Hugo J. Marquez
 * @description: Gesture Control Screen module
 *
 */

 // LED
 uint8_t led_count = 12;
 long sleep_count = 0;

 void setDisplay(){
   M5.Lcd.setRotation(3);
   M5.Lcd.fillScreen(BLACK);
   M5.Lcd.setTextSize(2);
   M5.Lcd.setCursor(30, 0);
   M5.Lcd.println("CI-N5-V");
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
