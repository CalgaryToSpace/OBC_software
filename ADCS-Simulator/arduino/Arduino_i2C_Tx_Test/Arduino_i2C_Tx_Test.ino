/*
* LAB Name: Arduino I2C Master(Tx)
* Author: Khaled Magdy
* For More Info Visit: www.DeepBlueMbedded.com
*/
#include <Wire.h>
 
uint8_t AN_POT;
 
void setup() {
  Wire.begin(); // Initialize I2C (Master Mode: address is optional)
  pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop() {
  AN_POT = 0x74;
  Wire.beginTransmission(0x57); // Transmit to device with address 0x57
  Wire.write(AN_POT);      // Sends Potentiometer Reading (8Bit)
  Wire.endTransmission();       // Stop transmitting

  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}