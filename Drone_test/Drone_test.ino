#include <Servo.h> //Using servo library to control ESC
#include <elapsedMillis.h> // Using elapsedMillis library
Servo esc; //Creating a servo class with name as esc

int JoyStick_X = 0; //x
int JoyStick_Y = 1; //y
int JoyStick_Z = 3; //key
bool stop;
elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
unsigned int interval = 2000;

void setup()
{
/*  To configure first time (may have to do for loop instead of the two lines)
  esc.writeMicroseconds(2000);
  esc.writeMicroseconds(1000);

  for (int i = 1000; i <= 2000; i++){ //Throttle up
    esc.writeMicroseconds(i);
    Serial.println("Forward : " + String(forward));
    delay(5);
  }
  for (int i = 2000; i >= 1000; i--){ //Throttle down
    esc.writeMicroseconds(i);
    delay(5);
  }*/
  
//  int pinFR = 8; // 4
//  int pinFL = 9; // 3
//  int pinBR = 10; // 1
//  int pinBL = 11; // 2
  int pin = 8; //Specify the pin connection (D8)
  esc.attach(pin); //Specify the esc signal pin
  Serial.begin(9600); //Setup input/output screen
  pinMode(JoyStick_Z, INPUT); 
  Serial.begin(9600); // 9600 bps

  /* Wait for press and release of the joystick */
  int z=digitalRead(JoyStick_Z);
  while (z == 0){
    Serial.println("Press Button");
    delay(500);  
    z=digitalRead(JoyStick_Z);
  }
  while (z == 1){
    Serial.println("Release Button");
    delay(500); 
    z=digitalRead(JoyStick_Z); 
  }
  stop = false;
  Serial.println("Done Setup");
}

void loop()
{
  /* Start of each loop (get values) */
  int x, y, z, val;
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);
  z=digitalRead(JoyStick_Z);

  if (stop == false){ // If stop is true dont do anything
    if (z == 1){ // If pressed stop
      esc.writeMicroseconds(1000);
      Serial.println("Stop");
      delay(500);
      while (z == 1 && stop == false){
        z=digitalRead(JoyStick_Z);
        if (timeElapsed > interval) {  
          Serial.println("Stop is true");     
          stop = true;
          timeElapsed = 0; // reset the counter to 0 so the counting starts over...
        }
        if (z == 0){
          break;
        }
        Serial.print("Elapsed Time (start stop): ");
        Serial.println(timeElapsed);
        delay(500);
      }
    } else{
      val = map(x, 0, 1023, 1200, 2000);
      esc.writeMicroseconds(val);
      Serial.print("MAPPED VALUE: ");
      Serial.println(val);
      Serial.print("X: ");
      Serial.print(x);
      Serial.print(", Y: ");
      Serial.print(y);
      Serial.print(", Z: ");
      Serial.print(z);
      delay(500);
    }
  } else{
    esc.writeMicroseconds(1000);
    Serial.println("Stop");
    delay(500);
    // Push and release to start again
    while (z == 1 && stop == true){
      z=digitalRead(JoyStick_Z);
      if (timeElapsed > interval) {  
        Serial.println("Stop is false");     
        stop = false;
        timeElapsed = 0; // reset the counter to 0 so the counting starts over...
      }
      Serial.print("Elapsed Time (start run): ");
      Serial.println(timeElapsed);
      delay(500);
    }
  }
}


// RAMP UP AND RAMP DOWN
//Throttle up and down to configure ESC (5 secods to throttle up and 5 seconds to throttle down - can change the delay to change the throttle up and down times)
//  for (int i = 1000; i <= 2000; i++){ //Throttle up
//    esc.writeMicroseconds(i);
//    Serial.print("RAMP UP: ");
//    Serial.println(i);
//    delay(5);
//  }
//  delay(20);
//  for (int i = 2000; i >= 1000; i--){ //Throttle down
//    esc.writeMicroseconds(i);
//    Serial.print("RAMP DOWN: ");
//    Serial.println(i);
//    delay(5);
//  }
//
//void loop() 
//{
//  int x,y,z;
//  x=analogRead(JoyStick_X);
//  y=analogRead(JoyStick_Y);
//  z=digitalRead(JoyStick_Z);
//  /* Z Direction */
//  if (z == 1){
//    Serial.print("Pressed: ");
//  } else{
//    Serial.print("Depressed: ");
//  }
//  /* X and Y Directions */
//  if ((x < 525 && x > 500) && (y < 525 && y > 500)){ /* Center */
//    Serial.println("Center");
//  } else if (x >= 525){ /* Right */
//    if (y >= 525){ /* SE */
//      Serial.println("South - East");
//    } else if (y <= 500){ /* NE */
//      Serial.println("North - East");
//    } else{ /* E */
//      Serial.println("East");
//    }
//  } else if (x <= 500){ /* Left */
//    if (y >= 525){ /* SW */
//      Serial.println("South - West");
//    } else if (y <= 500){ /* NW */
//      Serial.println("North - West");
//    } else{ /* W */
//      Serial.println("West");
//    }
//  } else{ /* Center */
//    if (y >= 525){ /* S */
//      Serial.println("South");
//    } else if (y <= 500){ /* N */
//      Serial.println("North");
//    }
//  }
//  delay(1000);
//}



  /*int val = 10;//Can change this to any number between 0 and 1000
  val = map(val, 0, 1023, 1000, 2000); //converts inputed value (0-1023) to ouput value for ESC (1000-2000)
  esc.writeMicroseconds(val);
  delay(5000);//run for 5 seconds*/  

