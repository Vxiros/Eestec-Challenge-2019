#include <TLE94112.h>
#include <TLE94112_Motor.h>

// Tle94112Motor Objects
Tle94112Motor motor1(tle94112, tle94112.TLE_PWM1);
Tle94112Motor motor2(tle94112, tle94112.TLE_PWM2);


void setup()
{
  // Enable MotorController Tle94112
  // Note: Required to be done before starting to configure the motor
  tle94112.begin();

  motor1.connect(tle94112.TLE_HB1, motor1.HIGHSIDE);
  motor1.connect(tle94112.TLE_HB2, motor1.HIGHSIDE);
  motor1.connect(tle94112.TLE_HB5, motor1.LOWSIDE);
  motor1.connect(tle94112.TLE_HB6, motor1.LOWSIDE);

  // Connect motor2 to HB2 and HB4
  motor2.connect(tle94112.TLE_HB7, motor2.LOWSIDE);
  motor2.connect(tle94112.TLE_HB8, motor2.LOWSIDE);
  motor2.connect(tle94112.TLE_HB11, motor2.HIGHSIDE);
  motor2.connect(tle94112.TLE_HB12, motor2.HIGHSIDE);

  //when configuration is done, call begin to start operating the motors
  motor1.begin();
  motor2.begin();

  Serial.begin(9600);
}

// Speed should not exceed 100 on tank robot.

void loop()
{
  motor1.setSpeed(0);
  motor2.setSpeed(0);

  int m1, m2, bug;

  while(!Serial.available()>0) {}
      m1 = Serial.parseInt(); bug = Serial.parseInt();
      Serial.println("m1");
      Serial.println(m1);Serial.read();

  while(!Serial.available()>0) {}
      m2 = Serial.parseInt(); bug = Serial.parseInt();
      Serial.println("m2");
      Serial.println(m2);Serial.read();

  while(true) {
  motor1.setSpeed(m1);
  motor2.setSpeed(m2);
  }
  delay(5);
}
