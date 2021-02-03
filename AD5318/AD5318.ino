#include <SPI.h>
#define SS_PIN 10
#define DIV 511
int16_t counter = 0;
void setup() {
  Serial.begin(115200);
  SPI.begin();
  digitalWrite(SS_PIN,HIGH);
}

void loop() {
  Serial.println(analogRead(A0)); 
  //CHA~H=CH0~7
  set_voltage(1,512*(1+sin(2*3.14592*counter/DIV)));
  counter++;
  if(counter > DIV)counter=0;
  delay(1);
}
void set_voltage(int8_t channel,int16_t value){
  if(channel<0||channel>7||value<0||value>1023)return;
  int16_t buffer=((channel<<12)&0x7000)|((value<<2)&0x0FFC);
  digitalWrite(SS_PIN,LOW);
  SPI.transfer((uint8_t)((buffer & 0xFF00) >>  8));
  SPI.transfer((uint8_t)((buffer & 0x00FF) >>  0));
  digitalWrite(SS_PIN,HIGH);
}
