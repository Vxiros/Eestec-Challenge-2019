#include "dht.h"
#define dht_inside A0
#define dht_outside A4
#define Analog_Eingang A2
#define LIGHTSENSOR_INSIDE A1
#define LIGHTSENSOR_OUTSIDE A3
#define lights_desk A5
#define lights_seats A6
#define parathiro_open 1000
#define parathiro_close 1001
#define skiastro_up 1002
#define skiastro_down 1003
#define klimatismos 1004
#define microphone 1005
#define porta_eisodou_triger 0
#define porta_eisodou_echo 1
#define porta_eksodou_triger 2
#define porta_eksodou_echo 3

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
      digitalWrite(porta_eisodou_triger, LOW);  
      delayMicroseconds(2); 
      digitalWrite(porta_eisodou_echo, HIGH);
      delayMicroseconds(10); 
      digitalWrite(porta_eisodou_triger, LOW);
      duration = pulseIn(porta_eisodou_echo, HIGH);
      distance = (duration/2) / 29.1;
      if (distance < 70 && distance >0){
        counter++;       
      }
      digitalWrite(porta_eksodou_triger, LOW);  
      delayMicroseconds(2); 
      digitalWrite(porta_eksodou_echo, HIGH);
      delayMicroseconds(10); 
      digitalWrite(porta_eksodou_triger, LOW);
      duration = pulseIn(porta_eksodou_echo, HIGH);
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
    pinMode(parathiro_open,OUTPUT);
    pinMode(parathiro_close,OUTPUT);
    digitalWrite(parathiro_open,LOW);
    digitalWrite(parathiro_close,HIGH);
    pinMode(skiastro_up,OUTPUT);
    pinMode(skiastro_down,OUTPUT);
    digitalWrite(skiastro_down,LOW);
    digitalWrite(skiastro_up,HIGH);
    pinMode(klimatismos,OUTPUT);
    digitalWrite(klimatismos,LOW);
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
      digitalWrite(porta_eisodou_triger, LOW);
      duration = pulseIn(porta_eisodou_echo, HIGH);
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
    Serial.print("Oi mathites pou kathontai einai "); Serial.println(count_seated_students);
    
}


void loop(){
  //Start of Program 


//------------------
//    THEMA B
//------------------
  
    //----------------
    // ERWTIMA 1
    //---------------
    CalculateStudents();
    TempAndHum();
    Sound();
    Light();
    
    //------------------
    //  ERWTIMA 2
    //------------------
     if (automode == HIGH){
      if (light_inside < 250 && counter>0){
        if (light_outside <=250){
          digitalWrite(lights_desk,HIGH);
          digitalWrite(lights_seats,HIGH);     
          digitalWrite(skiastro_up,LOW);
          digitalWrite(skiastro_down,HIGH);
        }
      }
      if (light_outside > 250){
        digitalWrite(skiastro_down,LOW);
        digitalWrite(skiastro_up,HIGH);
        digitalWrite(lights_desk,LOW);
        digitalWrite(lights_seats,LOW);       
      }
     }

    //------------------
    //  ERWTIMA 3
    //------------------
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
    
    //------------------
    //  ERWTIMA 4
    //------------------ 
    if (temp_inside!= 25 && counter>0){
      if (temp_outside!=25){
        digitalWrite(klimatismos,HIGH);
        digitalWrite(parathiro_open,LOW); digitalWrite(parathiro_close,HIGH);
      }
      else {
        digitalWrite(klimatismos,LOW);
        digitalWrite(parathiro_open,HIGH); digitalWrite(parathiro_close,LOW); }
    } 


    
    //------------------
    //  ERWTIMA 5
    //------------------
    if (counter==0){
      digitalWrite(lights_desk,LOW);
      digitalWrite(lights_seats,LOW);
    }


    
    //------------------
    //  ERWTIMA 6
    //------------------
    if (counter == 0 ) counter_loops++;
    else counter_loops=0;
    if (counter_loops >=600) digitalWrite(klimatismos,LOW);


    
    //------------------
    //  ERWTIMA 7
    //------------------
    if (Analog >=255 && Analog<=1023){
      analogWrite(microphone,Analog/255);
    }

    

//------------------------------
//         THEMA G
//------------------------------
    CaclulateStudentsinSeat();
}
