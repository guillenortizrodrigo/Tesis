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
  
  for(int stepNumber=1; stepNumber<5;stepNumber++){
    transferData(stepNumber, B11110000, B10101010);
    
  }
  
}

void transferData(int stepNumber, byte byte1, byte byte2){
  
  byte response; 
  
  response = SPI.transfer(stepNumber); 
  Serial.println(response); 
  
  response = SPI.transfer(byte1); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte2); 
  Serial.println(response, BIN); 

}

void loop() {
  // put your main code here, to run repeatedly
  
  
}
