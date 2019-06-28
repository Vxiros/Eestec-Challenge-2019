#include "dht.h"
#define dht_inside A0
#define dht_outside A4
#define Analog_Eingang A2
#define LIGHTSENSOR_INSIDE A1
#define LIGHTSENSOR_OUTSIDE A3
#define lights_desk A5
#define lights_seats A6
#define window_open 1000
#define window_close 1001
#define tent_up 1002
#define tent_down 1003
#define air_condition 1004
#define microphone 1005
#define in_door_triger 0
#define in_door_echo 1
#define out_door_triger 2
#define out_door_echo 3

int trigPin[35];
int echoPin[35];
dht DHT_OUTSIDE;
dht DHT_INSIDE;
int counter=0;
int counter_loops=0;
int light_inside,light_outside;
int temp_inside;
int temp_outside;
int Analog;
bool automode= HIGH;
bool Enable[15];

void TempAndHum(){
    DHT_OUTSIDE.read11(dht_outside);
    DHT_INSIDE.read11(dht_inside);
    Serial.print("The temperature inside of amphitheater is ");
    temp_inside=DHT_INSIDE.temperature;
    temp_outside=DHT_OUTSIDE.temperature;
    Serial.print(temp_inside); Serial.println("C ");\
    Serial.print("The temperature outside of amphitheater is ");
    Serial.print(temp_outside); Serial.println("C ");\
    
}
void CalculateStudents(){
    
      long duration, distance;
      digitalWrite(in_door_triger, LOW);  
      delayMicroseconds(2); 
      digitalWrite(in_door_echo, HIGH);
      delayMicroseconds(10); 
      digitalWrite(in_door_triger, LOW);
      duration = pulseIn(in_door_echo, HIGH);
      distance = (duration/2) / 29.1;
      if (distance < 70 && distance >0){
        counter++;       
      }
      digitalWrite(out_door_triger, LOW);  
      delayMicroseconds(2); 
      digitalWrite(out_door_echo, HIGH);
      delayMicroseconds(10); 
      digitalWrite(out_door_triger, LOW);
      duration = pulseIn(out_door_echo, HIGH);
      distance = (duration/2) / 29.1;
      if (distance < 70 && distance >0 ){
        if (counter>0) counter--;        
      }
      Serial.print("Number of students inside the amphitheater is ");
      Serial.println(counter);
}

void Sound(){
    Analog = analogRead (Analog_Eingang);
    Serial.print("Sound is ");Serial.println(Analog);
}

void Light(){
    light_inside = analogRead(LIGHTSENSOR_INSIDE);
    Serial.print("Light inside is ");Serial.print(light_inside);
    Serial.println(" lux");
    light_outside = analogRead(LIGHTSENSOR_OUTSIDE);
    Serial.print("Light outside is ");Serial.print(light_outside);
    Serial.println(" lux");
}

void setup(){
 
    Serial.begin(9600);
    for (int i=4;i<=34;i++){
      trigPin[i]= i;
      echoPin[i]= 2*i;
    }
    for (int i=4;i<=34;i++){
      pinMode(trigPin[i], OUTPUT);
      pinMode(echoPin[i], INPUT);
    }
    for (int i=0; i<15; i++){
      Enable[i]= false;
    }
    pinMode (Analog_Eingang, INPUT);
    pinMode(LIGHTSENSOR_INSIDE,  INPUT);
    pinMode(LIGHTSENSOR_OUTSIDE,  INPUT);
    pinMode(lights_desk, OUTPUT);
    pinMode(lights_seats, OUTPUT);
    digitalWrite(lights_desk,LOW);
    digitalWrite(lights_seats,LOW);
    pinMode(window_open,OUTPUT);
    pinMode(window_close,OUTPUT);
    digitalWrite(window_open,LOW);
    digitalWrite(window_close,HIGH);
    pinMode(tent_up,OUTPUT);
    pinMode(tent_down,OUTPUT);
    digitalWrite(tent_down,LOW);
    digitalWrite(tent,HIGH);
    pinMode(air_condition,OUTPUT);
    digitalWrite(air_condition_LOW);
    pinMode(microphone,OUTPUT);
    analogWrite(microphone,1);
    //delay(1000);//Wait before accessing Sensor
 
}

void CaclulateStudentsinSeat(){
    int count_seated_students=0;
    for (int i=4; i<=34; i++){
      long duration, distance;
      digitalWrite(trigPin[i], LOW);  
      delayMicroseconds(2); 
      digitalWrite(echoPin[i], HIGH);
      delayMicroseconds(10); 
      digitalWrite(in_door_triger, LOW);
      duration = pulseIn(in_door_echo, HIGH);
      distance = (duration/2) / 29.1;
      if ( i%2 == 0 ){
        if ( distance < 80 ) count_seated_students+= 4;
        else if(distance <160 ) count_seated_students+= 3;
        else if(distance <240 ) count_seated_students+= 2;
        else if(distance <320 ) {
          count_seated_students+= 1;
          if (Enable[(i-4)/2] == false) {Serial.print("Enable Row "); Serial.println((i-4/2)+1); Enable[(i-4)/2]= true;}
        }
        else { 
          if (Enable[(i-4)/2] == true) {Serial.print("Disable Row "); Serial.println((i-4/2)+1); Enable[(i-4)/2]= false;}
          break;
        }
      }else{
        if ( distance < 80 ) count_seated_students+= 5;
        else if(distance <160 ) count_seated_students+= 4;
        else if(distance <240 ) count_seated_students+= 3;
        else if(distance <320 ) count_seated_students+= 2;
        else if(distance < 400) count_seated_students+= 1;
        else break;
      }
    }
    Serial.print("They are "); Serial.print(count_seated_students); Serial.println(" students seated!");
    
}


void loop(){
  //Start of Program 
    CalculateStudents();
    TempAndHum();
    Sound();
    Light();
    
    if (automode == HIGH){
      if (light_inside < 250 && counter>0){
        if (light_outside <=250){
          digitalWrite(lights_desk,HIGH);
          digitalWrite(lights_seats,HIGH);     
          digitalWrite(tent_up,LOW);
          digitalWrite(tent_down,HIGH);
        }
      }
      if (light_outside > 250){
        digitalWrite(tent_down,LOW);
        digitalWrite(tent_up,HIGH);
        digitalWrite(lights_desk,LOW);
        digitalWrite(lights_seats,LOW);       
      }
     }

    if (Serial.available() > 0){
      automode=LOW;
      String input=Serial.readString();
      if (input == "A") {digitalWrite(lights_desk,LOW); digitalWrite(lights_seats,HIGH);}
      else if (input =="E"){ digitalWrite(lights_desk,HIGH); digitalWrite(lights_seats,LOW);}
      else if (input == "ON"){ digitalWrite(lights_desk,HIGH); digitalWrite(lights_seats,HIGH);}
      else if (input == "OFF"){ digitalWrite(lights_desk,LOW); digitalWrite(lights_seats,LOW);}
      else if (input == "AUTO") automode=HIGH;
      else automode=HIGH;
    } 

    if (temp_inside!= 25 && counter>0){
      if (temp_outside!=25){
        digitalWrite(air_condition,HIGH);
        digitalWrite(window_open,LOW); digitalWrite(window_close,HIGH);
      }
      else {
        digitalWrite(klimatismos,LOW);
        digitalWrite(window_open,HIGH); digitalWrite(window_close,LOW); }
    } 


    if (counter==0){
      digitalWrite(lights_desk,LOW);
      digitalWrite(lights_seats,LOW);
    }


    if (counter == 0 ) counter_loops++;
    else counter_loops=0;
    if (counter_loops >=600) digitalWrite(air_condition,LOW);

    if (Analog >=255 && Analog<=1023){
      analogWrite(microphone,Analog/255);
    }

    CaclulateStudentsinSeat();
}
