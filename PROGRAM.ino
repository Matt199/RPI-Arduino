//#include <AFMotor.h>
#include <Servo.h>              
Servo servo1;               
Servo servo2;

int  counter = 0;
int sum = 0;
int sum_prev = 0;

int solarVoltage = 0;
float voltage = 0;

int photoRes_A1 = 0;
int photoRes_A2 = 0;
int photoRes_A3 = 0;
int photoRes_A4 = 0;

int servo_position = 0 ;
int fixedStep = 5;

void servo(int s_position){
  servo1.write(s_position);
  servo2.write(180 - s_position);
}

void measureLight(){

    photoRes_A1 = analogRead(A1);
    photoRes_A2 = analogRead(A2);
    photoRes_A3 = analogRead(A3);
    photoRes_A4 = analogRead(A4);
    
  }

void setup() {
  Serial.begin(9600);
  
  servo1.attach (10);
  servo2.attach (9);
  servo1.write(servo_position);
  servo2.write(180 - servo_position);
  
}

void loop() {

  solarVoltage = analogRead(A0);
  voltage = solarVoltage * (22.0/102.3);
  //Serial.println(voltage);

  /*photoRes_A1 = analogRead(A1);
  photoRes_A2 = analogRead(A2);
  photoRes_A3 = analogRead(A3);
  photoRes_A4 = analogRead(A4);
  sum_prev = photoRes_A1 + photoRes_A2 + photoRes_A3 + photoRes_A4;*/

  servo_position += 10;
  servo1.write(servo_position);
  servo2.write(180 - servo_position);
  
  photoRes_A1 = analogRead(A1);
  photoRes_A2 = analogRead(A2);
  photoRes_A3 = analogRead(A3);
  photoRes_A4 = analogRead(A4);
  sum = photoRes_A1 + photoRes_A2 + photoRes_A3 + photoRes_A4;
  
  if( sum < (sum_prev + 15)){
    servo_position += 10;
    servo1.write(servo_position);
    delay(10);
    servo2.write(180 - servo_position);
    delay(10);
    Serial.print("+");
  }
  else if ( sum > (sum_prev + 15)){
    servo_position -= 10;
    servo1.write(servo_position);
    delay(10);
    servo2.write(180 - servo_position);
    delay(10);
    Serial.print("-");
  }
  Serial.println(sum);
  //Serial.print(servo_position);
  //Serial.println();
  //Serial.println();
  sum_prev = sum;
  delay(600);
}


