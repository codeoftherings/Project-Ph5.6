#include <LWiFi.h>
#include <LWiFiClient.h>
#include <LWiFiServer.h>
#include <LWiFiUdp.h>
#include <BlynkSimpleLinkItONE.h>
#define WIFI_AP "hello"
#define WIFI_PWD "12345678"
#define WIFI_AUTH LWIFI_WPA
#define trig 6
#define echo 7
char auth[]= "e9dbd11e00c04b959aa140d57014c092";
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
 if(LWiFi.connectWEP(WIFI_AP, WIFI_PASSWORD) < 0)
{
  while(true)
segregate();

}
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
    Blynk.virtualWrite(2,"Good");
    
     if(water_level()>=80)
    
    {
      if(analogRead(A0)<=400)
      {
         digitalWrite(8,LOW);
        delay(10000);
        digitalWrite(8,HIGH);
      }
      else if(analogRead(A0)<=600)
    {
      digitalWrite(10,LOW);
        delay(10000);
        digitalWrite(10,HIGH);
    }
      else 
    {
       digitalWrite(11,LOW);
        delay(10000);
        digitalWrite(11,HIGH);
    }
        
    }
   
   
   
    delay(500);
    

}


