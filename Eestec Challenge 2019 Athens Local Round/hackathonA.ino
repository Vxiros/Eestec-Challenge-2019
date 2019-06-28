#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to
#define trigPin 13
#define echoPin 12
#define Analog_Eingang A2
#define LIGHTSENSORPIN A1

dht DHT;

void TempAndHum(){
    DHT.read11(dht_apin);
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
}
void Distance(){
    long duration, distance;
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    if (distance >= 500 || distance <= 0){
      Serial.println("Distance is Out of range");
    }
    else{
      Serial.print("distance is ");
      Serial.print(distance);
      Serial.println(" cm");
    }
}

void Sound(){
    int Analog;
    Analog = analogRead (Analog_Eingang);
    Serial.print("Sound is ");Serial.println(Analog);
}

void Light(){
    int reading = analogRead(LIGHTSENSORPIN);
    Serial.print("Light is ");Serial.print(reading);
    Serial.println(" lux");
}

void setup(){
 
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode (Analog_Eingang, INPUT);
    pinMode(LIGHTSENSORPIN,  INPUT);
    //delay(1000);//Wait before accessing Sensor
 
}
 
void loop(){
  //Start of Program 
    Distance();
    TempAndHum();
    Sound();
    Light();
    Serial.println("-----------------------------------------------");
    delay(2000);
}
