#include <SPI.h>

void setup() {
  //inicializar monitor serial: 
  Serial.begin(9600);

  //inicializar SPI
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);

}

void loop() {
  // put your main code here, to run repeatedly:

}
