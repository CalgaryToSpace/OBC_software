#include <Wire.h>

uint8_t tx_byte;
uint8_t rx_byte;

void I2C_RxHandler(void) {
  Serial.println("RX");
  while(Wire.available()) { 
    rx_byte = Wire.read();
  }
}

void I2C_TxHandler() {
  Serial.println("TX");
  Wire.write(tx_byte);
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x55); // need address for peripheral device
  Serial.begin(9600);
  Wire.onReceive(I2C_RxHandler); // controller sending data to peripheral
  Wire.onRequest(I2C_TxHandler); // controller wants data from peripheral
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
