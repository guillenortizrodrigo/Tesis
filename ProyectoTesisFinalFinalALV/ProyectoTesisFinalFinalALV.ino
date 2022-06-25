#include <SPI.h>

int slaveSelect = 2;

//ARREGLOS DE DATOS
const int slavesquantity = 1;
int slaves[slavesquantity] = {2};

int delaytime = 200;

void transferData(int stepNumber, byte byte1, byte byte2,int slave){
  byte response; 
  digitalWrite(slave,LOW);
  response = SPI.transfer(stepNumber); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte1); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte2); 
  Serial.println(response, BIN);
  digitalWrite(slave,HIGH);
}

void setup() {
    Serial.begin(9600);
    pinMode(slaveSelect,OUTPUT);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);

    
    for(int i=0; i<slavesquantity; i++){
      for(int stepNumber=1; stepNumber<5;stepNumber++){
        transferData(stepNumber, B11110000, B10101010,slaves[i]);
      }
    }
    

    digitalWrite(slaveSelect,LOW);
    byte response; 
    response = SPI.transfer(25); 
    Serial.println(response, BIN); 
    digitalWrite(slaveSelect,HIGH);
    
 }
 
void loop() {
    
}
