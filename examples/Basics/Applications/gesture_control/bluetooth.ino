/**
 * CI-N5-V
 * @author: Hugo J. Marquez
 * @description: Gesture Control BT module
 *
 */

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
