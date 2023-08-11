//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//

  int limitPin = 8;
  int servoPin = 3;

  bool stuck = false;
  bool InChamber = false;
  
  int orangeCount = 0;
  int blueCount = 0;
  int yellowCount = 0;
  int brownCount = 0;
  int greenCount = 0;
  int redCount = 0;
  int Count = 0;
  
#include <Stepper.h>
Stepper myStepper = Stepper(2048,2,6,4,7);

#include <Servo.h>
Servo myServo;

#include <Pixy2.h>
Pixy2 pixy;

void setup() {
  
  // set limit switch to input w/ pullup resistor
  pinMode(limitPin, INPUT_PULLUP);

  //Stepper motor, Servo motor, Pixy cam and serial port
  myStepper.setSpeed(15);
  myServo.attach(servoPin);
  myServo.write(80);
  pixy.init();
  pixy.setLamp(1,1);
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
}

void loop() {
  
  int j = 0;
  
  // get data from camera
  pixy.ccc.getBlocks();
  
  // rotate stepper motor/feeder until candy is detected
  if (InChamber == false) {
    myStepper.step(200);
  }
  
  // stop motor and sort if candy detected
  if (pixy.ccc.numBlocks) { 
    myStepper.step(0);
    
    InChamber = true;
    int color = pixy.ccc.blocks[j].m_signature;
    
    Sort(color);
  }
  
   Serial.print("Counter: \n");
   Serial.print("Orange M&M: ");
   Serial.println(orangeCount);
   Serial.print("Blue M&M: ");
   Serial.println(blueCount);
   Serial.print("Yellow M&M: ");
   Serial.println(yellowCount);
   Serial.print("Red M&M: ");
   Serial.println(redCount);
   Serial.print("Green M&M: ");
   Serial.println(greenCount);
   Serial.print("Brown M&M: ");
   Serial.println(brownCount);  
}

void Sort(int ID){
// Sorting function controls dropping/dispensing sequence
  switch (ID){
    case 1: myStepper.step(-1050); myServo.write(80); InChamber = false; orangeCount++; Count++;
    break;
    case 2: myServo.write(135); myStepper.step(1050); delay(200); myServo.write(80); InChamber = false; blueCount++; Count++;
    break;
    case 3: myServo.write(135); myStepper.step(-1050); delay(200); myServo.write(80); InChamber = false; yellowCount++; Count++;
    break;
    case 4: myStepper.step(1050); myServo.write(80); InChamber = false; brownCount++; Count++;
    break;
    case 5: myServo.write(37); myStepper.step(1050); delay(200); myServo.write(80); InChamber = false; greenCount++; Count++;
    break;
    case 6: myServo.write(37); myStepper.step(-1050); delay(200); myServo.write(80); InChamber = false; redCount++; Count++;
    break;
  }
}
