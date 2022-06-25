#include <SPI.h>

int slaveSelect = 2;
int delaytime = 200;
int i = 0; 

void transferData(int stepNumber, byte byte1, byte byte2){
  
  byte response; 
  
  response = SPI.transfer(stepNumber); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte1); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte2); 
  Serial.println(response, BIN); 

}

void setup() {
    Serial.begin(9600);
    pinMode(slaveSelect,OUTPUT);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    
    for(int stepNumber=1; stepNumber<5;stepNumber++){
      transferData(stepNumber, B11110000, B10101010);
    }
    
 }
 
void loop() {
    if (i >= 256){
      //reiniciamos el contador
      i = 0; 
    }
    
    digitalWrite(slaveSelect,LOW);
    int m = SPI.transfer(i);
    digitalWrite(slaveSelect,HIGH);
    delay(delaytime);
    Serial.println(m);
    
    
    i++;
}
