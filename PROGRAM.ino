//#include <AFMotor.h>
#include <Servo.h>              
Servo servo1;               
Servo servo2;

//int  counter = 0;
int solarVoltage = 0;
float voltage = 0;

int photoRes_A1 = 0;
int photoRes_A2 = 0;
int photoRes_A3 = 0;
int photoRes_A4 = 0;

int sum = 0;
int sum_prev = 0;

int servo_position = 0 ;
int prev_servo_position = 0;

int potentiometer = 0;

const int fixedStep = 10;

void servo(int s_position){
  servo1.write(s_position);
  servo2.write(180 - s_position);
}

int measureLight(){
    photoRes_A1 = analogRead(A1);
    photoRes_A2 = analogRead(A2);
    photoRes_A3 = analogRead(A3);
    photoRes_A4 = analogRead(A4);
	
	return photoRes_A1 + photoRes_A2 + photoRes_A3 + photoRes_A4;
  }

void setup() {
  Serial.begin(9600);
  
  servo1.attach (10);
  servo2.attach (9);
  servo(servo_position);
  
  servo_position += fixedStep;
  servo(servo_position);
  sum_prev = measureLight();
}

void loop() {

  solarVoltage = analogRead(A0); //<0;0.5> [V]
  voltage = solarVoltage * (22.0/102.3); // <0;0.5> - <0;22> [V]
  Serial.println(voltage);
  
  potentiometer = analogRead(A5); 
  servo_position = map(potentiometer, 0, 1000, 0, 180); 
  
  
  //============HAND-ADJUST============
  
  if (abs(servo_position-prev_servo_position) > 5) { 
    servo(servo_position);
    prev_servo_position = servo_position; 
  }
  
  //=================================
 
 
  //============AUTO-ADJUST============
 /*
 
  sum = measureLight();
  
  if( sum < (sum_prev + 20) ){
    servo_position += fixedStep;
    servo(servo_position);
    delay(10);
  }
  else if( sum > (sum_prev + 20) ){
    servo_position -= fixedStep;
    servo(servo_position);
    delay(10);
  }
  
  sum_prev = sum;
  
   */
  //=================================
  
  delay(100);
}


