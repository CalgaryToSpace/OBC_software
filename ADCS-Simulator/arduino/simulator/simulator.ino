#include <Wire.h>
// Pins for Arduino Uno: A4 (SDA), A5 (SCL)
// Pins for Nucleo: A3 (PC1, SDA), A1 (PC0, SCL)

uint8_t tx_byte;
uint8_t rx_buffer[32];
uint32_t rx_count = 0;

/* CONFIGURATION */
#define I2C_ADDRESS 0x57 // same peripheral address as ADCS

void I2C_RxHandler(int bytes) {

  while(Wire.available()) { 
    rx_buffer[rx_count] = Wire.read();
    rx_count++;
  }
  rx_buffer[rx_count] = '\0';
  rx_count = 0;

  Serial.print("Received Data:");  
  Serial.println((char*)rx_buffer);  
  
}

void I2C_TxHandler() {
  Serial.println("Transmitting data...");
  Serial.println(tx_byte);
  Wire.write(tx_byte);
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