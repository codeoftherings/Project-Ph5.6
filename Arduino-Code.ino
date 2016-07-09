#include <LWiFi.h>
#include <LWiFiClient.h>
#include <LWiFiServer.h>
#include <LWiFiUdp.h>
#include <BlynkSimpleLinkItONE.h>
#define WIFI_AP "Sagnik"
#define WIFI_PWD "galinumberfive"
#define WIFI_AUTH LWIFI_WPA
#define trig 6
#define echo 7
char auth[]= "d16e55ff5c224ca192dacec821221773";
void segregate();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth,WIFI_AP,WIFI_PWD,WIFI_AUTH);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
   pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
   pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  //segregate();
}
int water_level()
{
  int tank_height=20;

    long duration,distance;
    digitalWrite(trig,LOW);
    delayMicroseconds(2);
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    duration=pulseIn(echo,HIGH);
    distance= (duration/29)/2;
    if(distance>tank_height)
    {
      distance=tank_height;
    }
    
    
    

  return (20-distance)*5;


}


BLYNK_READ(0){
      
    Blynk.virtualWrite(3,water_level());
    Blynk.virtualWrite(1,analogRead(A0));
    Blynk.virtualWrite(0,analogRead(A0));
    
     if(water_level()>=80)
    
    {
      Blynk.email("saggieb12@gmail.com", "You tank is full", "Hey! your tank is full. Use it well.");
      Blynk.tweet("I'm doing my bit to save water. I have just saved 20 litres.");
      if(analogRead(A0)<=400)
      {
         digitalWrite(8,LOW);
        delay(10000);
        digitalWrite(8,HIGH);
        Blynk.virtualWrite(2,"Bad");
      }
      else if(analogRead(A0)<=600)
    {
      digitalWrite(10,LOW);
        delay(10000);
        digitalWrite(10,HIGH);
        Blynk.virtualWrite(2,"Fair");
    }
      else 
    {
       digitalWrite(11,LOW);
        delay(10000);
        digitalWrite(11,HIGH);
        Blynk.virtualWrite(2,"Good");
    }
        
    }
   
   
   
    delay(500);
    

}

