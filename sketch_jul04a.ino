
#include "TimerOne.h"
// include the library code:
#include <LiquidCrystal.h>
 
// Constants for Interrupt Pins
// Change values if not using Arduino Uno
 
const byte MOTOR1 = 2;  // Motor 1 Interrupt Pin - INT 0
 
// Integers for pulse counters
unsigned int counter1 = 0;
 int sp=180;
// Float for number of slots in encoder disk
float diskslots = 20;  // Change to match value of encoder disk
 
// Interrupt Service Routines
 
// Motor 1 pulse count ISR

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void ISR_count1()  
{
  counter1++;  // increment Motor 1 counter value
} 
 
 
// TimerOne ISR
void ISR_timerone()
{
  Timer1.detachInterrupt();  // Stop the timer
  Serial.print("Motor Speed 1: "); 
  float rotation1 = (counter1 / diskslots) * 60.00;  // calculate RPM for Motor 1
  Serial.print(rotation1);  
  Serial.print(" RPM -  "); 
  Serial.print("\n");
  Serial.print(counter1);
  counter1 = 0;  //  reset counter to zero
 
  Timer1.attachInterrupt( ISR_timerone );  // Enable the timer
  // Print a message to the LCD.
  lcd.print(rotation1);
 
}
 
void setup() 
{
  Serial.begin(9600);
  
  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(digitalPinToInterrupt (MOTOR1), ISR_count1, RISING);  // Increase counter 1 when speed sensor pin goes High
  Timer1.attachInterrupt( ISR_timerone ); // Enable the timer
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
} 
 
void loop()
{
  // Nothing in the loop!
  // You can place code here

  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
}
 
