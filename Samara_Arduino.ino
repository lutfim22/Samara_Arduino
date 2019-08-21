#include <TinyGPS++.h>
#include <SoftwareSerial.h>

char command;
String string;
boolean ledon = false;
static const int RXPin = 8, TXPin = 11;
#define led 5
#define led2 6
#define led3 9
#define led4 10

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

  void setup()
  {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
  }

  void loop()
  {
    if (Serial.available() > 0) 
    {string = "";}
    
    while(Serial.available() > 0)
    {
      command = ((byte)Serial.read());
      
      if(command == ':')
      {
        break;
      }
      
      else
      {
        string += command;
      }
      
      delay(1);
    }
    
    if(string == "TO")
    {
        ledOn();
        ledon = true;
    }
    
    if(string =="TF")
    {
        ledOff();
        ledon = false;
        Serial.println(string);
    }
    
    if ((string.toInt()>=0)&&(string.toInt()<=255))
    {
      if (ledon==true)
      {
        analogWrite(led, string.toInt());
        Serial.println(string);
        delay(10);
      }
    }

    while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
      Serial.println(F("No GPS detected: check wiring."));
      while(true);
    }
 }
 
void ledOn()
   {
      analogWrite(led, 255);
      delay(100);
      analogWrite(led,0);
      delay(100);
      analogWrite(led2, 255);
      delay(100);
      analogWrite(led2,0);
      delay(100);
      analogWrite(led3, 255);
      delay(100);
      analogWrite(led3,0);
      delay(100);
      analogWrite(led4, 255);
      delay(100);
      analogWrite(led4,0);
      delay(100);
    }
 
 void ledOff()
 {
      analogWrite(led, 0);
      delay(10);
      analogWrite(led2, 0);
      delay(10);
      analogWrite(led3, 0);
      delay(10);
      analogWrite(led4, 0);
      delay(10);
 }

 void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }  
  Serial.println();
}
    
