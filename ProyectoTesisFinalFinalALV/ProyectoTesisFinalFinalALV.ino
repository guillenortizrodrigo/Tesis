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
  0.5
}; 
float delta[slavesquantity] = {
  .008
}; 
float measurementVoltage[slavesquantity] = {
  0.1
}; 
float voltageMaxReset[slavesquantity] = {
  0
}; 
float voltageMinReset[slavesquantity] = {
  -10485
}; 
float targetCurrent[slavesquantity] = {
  .000030
}; 



int delaytime = 200;

void transferData(int stepNumber, unsigned int valor,int slavePin){
  byte response; 
  digitalWrite(slavePin,LOW);
  delay(200);
  response = SPI.transfer(stepNumber);
  delay (100);
  Serial.println(response, BIN); 
  
  response = SPI.transfer(( uint8_t)(valor >> 8)); 
  Serial.println(response, BIN);
  delay (100); 
  
  response = SPI.transfer(( uint8_t)(valor)); 
  Serial.println(response, BIN);
  digitalWrite(slavePin,HIGH);
  delay (100);
}

unsigned int volts2bits(float volts){
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
            transferData(stepNumber, volts2bits(delta[i]) ,slaves[i]);
            break; 
          case 2: 
            //medicion?
            transferData(stepNumber, volts2bits(voltageMinSet[i]) + 32767 ,slaves[i]);
            break; 
          case 3: 
            transferData(stepNumber, volts2bits(voltageMaxSet[i]) + 32767 ,slaves[i]);
            break; 
          case 4: 
            transferData(stepNumber, volts2bits(measurementVoltage[i]) + 32767 ,slaves[i]);
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
