
#include <AFMotor.h> //Adafruit Motor Shield Library. First you must download and install AFMotor library
AF_DCMotor motor1 (1, MOTOR12_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
  AF_DCMotor motor2 (2, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  AF_DCMotor motor3 (3, MOTOR12_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
  AF_DCMotor motor4 (4, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency

unsigned long startMillis;  //some gllobal variables available anywhere in the program 
unsigned long currentMillis;
unsigned long period ; //the value is  a number of milliseconds
float sp=180;
float v=(32.5*2*PI*sp)/(60*1000);
void setup() {
 //Serial.begin(115200); //start serial IN ASE WE NEED TO PRINT DEBUGGING INFO
 startMillis= millis(); //initial start time

}

void loop() {
currentMillis=millis();  //get the current time (actually the number of milliseconds since the program started)
unsigned long d=Serial.read();
period=d*1000/v;
if (currentMillis- startMillis<=period) //test whether the period has elapsed 
{
  forward_car();
  }
  else stop_car();
}
void forward_car()
  {
  motor1.run(FORWARD);
  motor1.setSpeed(sp);
  motor2.run(FORWARD);
  motor2.setSpeed(sp);
  motor3.run(FORWARD);
  motor3.setSpeed(sp);
  motor4.run(FORWARD);
  motor4.setSpeed(sp);
  }
  void stop_car ()
{
motor1.run(RELEASE);
motor2.run(RELEASE);
motor3.run(RELEASE);
motor4.run(RELEASE);
//analogWrite(A3,LOW);
}
