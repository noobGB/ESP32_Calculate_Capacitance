/*
https://www.norwegiancreations.com/2019/08/using-a-simple-arduino-to-measure-capacitor-value/
time T=RC, to charge upto 63.2% of the supplied voltage
* we will first drain the capacitor by pulling capacitor_pin to LOW
* then will charge capacitor to 63.2%, will track of the time of charge by reading the analog value
* once we have the time T, then we will easily calculate C=T/R.
* I have done this experiment with 1000 uf capacitor, 96.3 K ohm resitor. 
* This program calculated 1015 uf, which is pretty good.
* Note : we can use lower value of resitor to fasten up the charging and discharging time, hence the program time to calculate the capacitance.
*/
#include <Arduino.h>

#define NO_MEASSUREMENTS 3
 
#define analog_pin     34
#define capacitor_pin  32
 
//#define resistor_value   96300.0F // the value on the resistor in Ohms
#define resistor_value   993.0F // 1k ohm //the value on the resistor in Ohms // this value is gud
 
unsigned long start_time = 0;
unsigned long accumulated_time = 0;
 
void setup() {
  pinMode(capacitor_pin, OUTPUT);
 
  Serial.begin(115200);
}
 
void loop() {
 
  accumulated_time = 0;
 
  for(uint8_t i = 0; i < NO_MEASSUREMENTS; i++){
 
    // Make sure the capacitor is dicharged
    Serial.print("loop");
    Serial.println(i);
    Serial.println((analogRead(analog_pin)/4));
    digitalWrite(capacitor_pin, LOW);
    while(analogRead(analog_pin) > 0){
    //Serial.println(analogRead(analog_pin)/4);
     //delay(1000);
    }
    Serial.println("Capacitor drained..!!");
     
    // set chargePin HIGH and capacitor charging an
    digitalWrite(capacitor_pin, HIGH);
    start_time = micros();
    Serial.println(start_time);
   
    // 647 is 63.2% of 1023, which corresponds to full-scale voltage
    while((analogRead(analog_pin)/4) <= 647){
     //Serial.println(analogRead(analog_pin)/4);
     //delay(1000); 
    }  
    accumulated_time += (micros() - start_time);  
  }  
 
  float result_time = ((float) accumulated_time) / NO_MEASSUREMENTS;
 
  float micro_F = ( result_time / resistor_value);
  Serial.print("Result time is : ");
  Serial.println((long)result_time);
  //print_float(micro_F, 2);
  if(micro_F>1)
  {
  Serial.print(micro_F);
  Serial.println(" uf");
  }
  else
  {
    micro_F=1000*micro_F;
    Serial.print(micro_F);
    Serial.println(" nf");
  }
  
  delay(5000);
}
 
