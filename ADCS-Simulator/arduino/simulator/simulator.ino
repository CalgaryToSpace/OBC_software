#include <Wire.h>
// Pins for Arduino Uno: A4 (SDA), A5 (SCL)
// Pins for Nucleo: A3 (PC1, SDA), A1 (PC0, SCL)

uint8_t tx_buffer[8] = {0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04};
uint32_t tx_count = 0;
uint8_t rx_buffer[32];
uint32_t rx_count = 0;

/* CONFIGURATION */
#define I2C_ADDRESS 0x57 // same peripheral address as ADCS

void I2C_RxHandler(int bytes) {

  Serial.print("Received Data: ");  

  while(Wire.available()) { 
    rx_buffer[rx_count] = Wire.read();
    Serial.print(rx_buffer[rx_count], HEX);
    Serial.print(" ");
    rx_count++;
  }

  rx_buffer[rx_count] = '\0';
  rx_count = 0;
  
  // Serial.println((char*)rx_buffer);  
  Serial.println();

}

void I2C_TxHandler() {
  Serial.println("Transmitting data...");

  for(tx_count = 0; tx_count < 4; tx_count++) { 
    // peripheral doesn't know how many bytes are requested
    // so we send bytes until no more are requested for now
      Serial.print(tx_buffer[tx_count], HEX);
      Wire.write(tx_buffer[tx_count]);
      Serial.print(" ");
    }
  Serial.println();
  tx_count = 0;
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2C_ADDRESS); // need address for peripheral device
  Serial.begin(9600);
  Wire.onReceive(I2C_RxHandler); // controller sending data to peripheral
  Wire.onRequest(I2C_TxHandler); // controller wants data from peripheral

  Serial.println();
  Serial.print("Peripheral is ready: Address 0x");
  Serial.println(I2C_ADDRESS, HEX);
  Serial.println("Waiting for data from controller...");  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}