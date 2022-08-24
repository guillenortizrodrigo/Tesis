#include <SPI.h>
const int clock = 7; 


int slaveSelect = 2;

//ARREGLOS DE DATOS
const int slavesquantity = 1;
int slaves[slavesquantity] = {
  2
};

float voltageMaxSet[slavesquantity] = {
  1.5 //volts
}; 
float voltageMinSet[slavesquantity] = {
  1
}; 
float delta[slavesquantity] = {
  .1
}; 
float measurementVoltage[slavesquantity] = {
  .5
}; 
float voltageMaxReset[slavesquantity] = {
  -22141
}; 
float voltageMinReset[slavesquantity] = {
  -10485
}; 
float targetCurrent[slavesquantity] = {
  .000030
}; 



int delaytime = 200;

void transferData(int stepNumber, byte byte1, byte byte2,int slavePin){
  byte response; 
  digitalWrite(slavePin,LOW);
  response = SPI.transfer(stepNumber); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte1); 
  Serial.println(response, BIN); 
  
  response = SPI.transfer(byte2); 
  Serial.println(response, BIN);
  digitalWrite(slavePin,HIGH);
}

int volts2bits(float volts){
  // convertir el voltaje ingresado por el usuario a 
  // bits para ser manejado por el programa. 
  float bits; 
  bits = volts * 13107; 
  
  return int(bits); 
}

void setup() {
    Serial.begin(9600);
    pinMode(slaveSelect,OUTPUT);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    
    pinMode(clock, OUTPUT); //manejo de la interrupcion 

    
    for(int i=0; i<slavesquantity; i++){
      for(int stepNumber=1; stepNumber<5;stepNumber++){
        switch (stepNumber){
          case 1: 
            transferData(stepNumber, ( uint8_t )( volts2bits(voltageMaxSet[i]) ),( uint8_t )( volts2bits(voltageMaxSet[i])>>8 ),slaves[i]);
            break; 
          case 2: 
            transferData(stepNumber, ( uint8_t )( volts2bits(voltageMaxSet[i]) ), ( uint8_t )( volts2bits(voltageMaxSet[i])>>8 ),slaves[i]);
            break; 
          case 3: 
            transferData(stepNumber, ( uint8_t )( volts2bits(voltageMaxSet[i]) ), ( uint8_t )( volts2bits(voltageMaxSet[i])>>8 ),slaves[i]);
            break; 
          case 4: 
            transferData(stepNumber, ( uint8_t )( volts2bits(measurementVoltage[i]) ), ( uint8_t )( volts2bits(measurementVoltage[i])>>8 ),slaves[i]);
            break; 
          default: {}
          
        
        }
      }
    }
    

    digitalWrite(slaveSelect,LOW);
    byte response; 
    response = SPI.transfer(25); 
    Serial.println(response, BIN); 
    digitalWrite(slaveSelect,HIGH);
    
 }
 
void loop() {
  
    digitalWrite (clock , HIGH); 
  delayMicroseconds(50);
  digitalWrite(clock, LOW); 
  delayMicroseconds(50);
}
