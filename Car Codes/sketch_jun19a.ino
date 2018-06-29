#include <AFMotor.h> //Adafruit Motor Shield Library. First you must download and install AFMotor library
  #include <Servo.h> //add Servo Motor library
  #include <NewPing.h> //add Ultrasonic sensor library
  //#include <RedBot.h> //add Line Follower sensor library
  AF_DCMotor motor1 (1, MOTOR12_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
  AF_DCMotor motor2 (2, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  AF_DCMotor motor3 (3, MOTOR12_1KHZ); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
  AF_DCMotor motor4 (4, MOTOR12_1KHZ); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  char h;
  int sp=180;
  int spS=60;
  #define TRIG_PIN A0 // Ultra
  #define ECHO_PIN A1
  #define MAX_DISTANCE 200
//line follower
  int left=17;
  int center=18;
  int right=19;

  int Left;
  int Center;
  int Right;

 
//UltraSonic
  NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
  Servo myservo;
  boolean goesForward=false;
  int distance = 100;
  int speedSet = 0;

  //Phase3
  unsigned long startMillis; //some gllobal variables available anywhere in the program 
 unsigned long currentMillis;
 unsigned long period ; //the value is  a number of milliseconds
float v=(32.5*2*PI*sp)/(60*1000);
float d;
//Void setup
  
  void setup() {
    
  Serial.begin(9600);
  //pinMode(A3,OUTPUT);
  myservo.attach(9);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
//  LineFollwer 
  pinMode(left,INPUT);
  pinMode(center,INPUT);
  pinMode(right,INPUT);
  delay(100);
  // Phase 3
  //Serial.begin(115200); //start serial IN ASE WE NEED TO PRINT DEBUGGING INFO
 startMillis= millis(); //initial start time
  
  }
  
  void loop() {
  if(Serial.available()){
  h=Serial.read();
  Serial.println(h);
  if(h=='C') {
  while(1){
  if(Serial.available()){
  h=Serial.read();
  if(h=='f')sp=150;
  if(h=='s')sp=200;
  if(h=='t')sp=255;
  if(h=='F')forward_car();
  if(h=='B')back_car();
  if(h=='R')right_car();
  if(h=='L')left_car();
  if(h=='K')forward_right_car();
  if(h=='P')forward_left_car();
  if(h=='M')back_right_car();
  if(h=='N')back_left_car();
  if(h=='S')stop_car ();
  }
  if(h=='c'){stop_car ();break;}
  }
  }

 if(h='z'){
  
    while(1)
    {
currentMillis=millis();  //get the current time (actually the number of milliseconds since the program started)
if (Serial.available()>0){
   d=Serial.parseFloat();
   period=(d)*1000/v;
if (currentMillis - startMillis <= period) //test whether the period has elapsed 
{
  forward_car();
  //currentMillis=millis();
  startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  
  }
  else stop_car();
}}}
  
  if(h=='V') {
  while(1){
  //Begining
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  if(distance<=35)
  {
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);
  if(distanceR>=distanceL)
  {
  turnRight();
  moveStop();
  }
  else
  {
  turnLeft();
  moveStop();
  }
  }
  else moveForward();
  distance = readPing();
  if(Serial.available()){
  h=Serial.read();
  }
  if(h=='v'){stop_car ();break;}
  }
  }
  if(h=='U'){
    while(1){
      Left=digitalRead(left);
Center=digitalRead(center);
Right=digitalRead(right);
if((Left==0 && Center==0 && Right==0)||(Left==1 && Center==0 &&Right==1))
{
  forward_car();
  Serial.println("forward");
  
}
else if(Left==0 && Center==0 && Right==1)
{
  right_car();
    Serial.println("right");

  if(Left=0 &&Center==1 &&Right==0){
  right_car();
    Serial.println("right");

  }
    
}
else if (Left==0 && Center==1 && Right==1)
{
  right_car();
      Serial.println("right");

  if(Left=0 &&Center==1 &&Right==0){
  right_car();
      Serial.println("right");

  }
  
}
else if(Left==1 && Center==0 && Right==0){

  left_car();
      Serial.println("left");

  if(Left=0 &&Center==1 &&Right==0){
  left_car();
      Serial.println("left");

  }
}
else if(Left==1 && Center==1 && Right==0)
{
  left_car();
      Serial.println("left");

 if(Left=0 &&Center==1 &&Right==0){
  left_car();
      Serial.println("left");

  }

}
//else if((Left=0 &&Center==1 &&Right==0)||(Left==1 && Center==1 &&Right==1)||(Left==1 && Center==0 &&Right==1))
  //moveStop();
  
  
    if(Serial.available()){
  h=Serial.read();
  }
  if(h=='u'){stop_car ();break;}
    }
  }
  }
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
  void back_car()
  {
  motor1.run(BACKWARD);
  motor1.setSpeed(sp);
  motor2.run(BACKWARD);
  motor2.setSpeed(sp);
  motor3.run(BACKWARD);
  motor3.setSpeed(sp);
  motor4.run(BACKWARD);
  motor4.setSpeed(sp);
 // digitalWrite(A3,HIGH);
  }
  void right_car()
  {
  motor1.run(BACKWARD);
  motor1.setSpeed(sp);
  motor2.run(FORWARD);
  motor2.setSpeed(sp);
  motor3.run(BACKWARD);
  motor3.setSpeed(sp);
  motor4.run(FORWARD);
  motor4.setSpeed(sp);
  }
  void left_car()
  {
  motor1.run(FORWARD);
  motor1.setSpeed(sp);
  motor2.run(BACKWARD);
  motor2.setSpeed(sp);
  motor3.run(FORWARD);
  motor3.setSpeed(sp);
  motor4.run(BACKWARD);
  motor4.setSpeed(sp);
  }
  void forward_right_car()
  {
  motor1.run(RELEASE);
  motor1.setSpeed(sp);
  motor2.run(FORWARD);
  motor2.setSpeed(sp);
  motor3.run(RELEASE);
  motor4.run(FORWARD);
  }
  void forward_left_car()
  {
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  motor3.run(FORWARD);
  motor3.setSpeed(sp);
  motor4.run(RELEASE);
  motor4.setSpeed(sp);
  }
  void back_right_car()
  {
  motor1.run(RELEASE);
  motor1.setSpeed(sp);
  motor2.run(BACKWARD);
  motor2.setSpeed(sp);
  motor3.run(RELEASE);
  motor4.run(BACKWARD);
  }
void back_left_car()
{
motor1.run(BACKWARD);
motor2.run(RELEASE);
motor3.run(BACKWARD);
motor3.setSpeed(sp);
motor4.run(RELEASE);
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
int lookRight()
{
myservo.write(50);
delay(500);
int distance = readPing();
delay(100);
myservo.write(115);
return distance;
}
int lookLeft()
{
myservo.write(170);
delay(500);
int distance = readPing();
delay(100);
myservo.write(115);
return distance;
delay(100);
}
int readPing() {
delay(70);
int cm = sonar.ping_cm();
if(cm==0)
{
cm = 250;
}
return cm;
}
void moveStop() {
motor1.run(RELEASE);
motor2.run(RELEASE);
motor3.run(RELEASE);
motor4.run(RELEASE);
}
void moveForward() {
motor1.run(FORWARD);
motor1.setSpeed(180);
motor2.run(FORWARD);
motor2.setSpeed(180);
motor3.run(FORWARD);
motor3.setSpeed(180);
motor4.run(FORWARD);
motor4.setSpeed(180);
}
void moveBackward() {
motor1.run(BACKWARD);
motor1.setSpeed(180);
motor2.run(BACKWARD);
motor2.setSpeed(180);
motor3.run(BACKWARD);
motor3.setSpeed(180);
motor4.run(BACKWARD);
motor4.setSpeed(180);
}
void turnRight() {
motor1.run(BACKWARD);
  motor1.setSpeed(220);
  motor2.run(FORWARD);
  motor2.setSpeed(220);
  motor3.run(BACKWARD);
  motor3.setSpeed(220);
  motor4.run(FORWARD);
  motor4.setSpeed(220);
delay(300);
moveForward();
}
void turnLeft() {
 motor1.run(FORWARD);
  motor1.setSpeed(220);
  motor2.run(BACKWARD);
  motor2.setSpeed(220);
  motor3.run(FORWARD);
  motor3.setSpeed(220);
  motor4.run(BACKWARD);
  motor4.setSpeed(220);
delay(300);
moveForward();
}
