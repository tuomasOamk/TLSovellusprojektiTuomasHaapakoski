#include "accelerator.h"
#include "messaging.h"

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0,OUTPUT);
digitalWrite(A0,HIGH);
pinMode(A4,OUTPUT);
digitalWrite(A4,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
Accelerator Aobject;
Messaging Mobject;
Serial.println("Give number how many measurements");
int NumberOfMeasurements = 0;
int flags = 0;
while(NumberOfMeasurements==0)
{
  if(Serial.available()>0)
  {
   
   NumberOfMeasurements = Serial.parseInt ();
   Serial.println("anna asento 1-6") 
   Aobject.makeMeasurement();
   Measurement foo = Aobject.getMeasurement();
   Serial.println(foo.x);
   Serial.println(foo.y);
   Serial.println(foo.z);
   
   
  }
}
while(flags==0)
{
  if(Serial.available()>0)
  {
    flags = Serial.parseInt();
  }
}
for(int M = 0;M<NumberOfMeasurements;M++)
{
  Aobject.makeMeasurement();
  Measurement m = Aobject.getMeasurement();
  uint8_t id = M;
  //uint8_t flags = 0xff;
  Mobject.createMessage(m);
  if(Mobject.sendMessage(id,flags))
  {
    Serial.println("Successfull transmission");
  }
  else
  {
    Serial.println("Transmission fails");
  }
  if(Mobject.receiveACK())
  {
    Serial.println("Receiver got message, going to next measurement");
  }
  else
  {
    Serial.println("Receiver did not get the message. Need to resend it");
    //M--; //Rewind loop

    
  }
}
return; }
