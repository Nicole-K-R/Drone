#include <Servo.h> //Using servo library to control ESC
#include <elapsedMillis.h> // Using elapsedMillis library
Servo esc; //Creating a servo class with name as esc

int JoyStick_X = 0; //x
int JoyStick_Y = 1; //y
int JoyStick_Z = 3; //key
int stopLight = 0;
int runLight = 1;
//  int pinFR = 8; // 4
//  int pinFL = 9; // 3
//  int pinBR = 10; // 1
//  int pinBL = 11; // 2
bool stop;
elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
unsigned int interval = 2000;

// Set the speed of all 4 motors
void setSpeedAll(int var){
  Serial.print("Setting speed to: ");
  Serial.println(var);
  esc.writeMicroseconds(var);
  if (var == 1000){
    Serial.println("Stop");
  }
  delay(1000);
}

// Toggle between off (stop) and on (run)
bool toggleOnOff(bool off){ // Off is the current value
  int z=digitalRead(JoyStick_Z);
  timeElapsed = 0; // Reset the counter to 0 so the counting starts over
  while (z == 1 && stop == off){
    Serial.println("------------- z is 1 -------------");
    z=digitalRead(JoyStick_Z);
    Serial.print(timeElapsed);
    Serial.print(" > ");
    Serial.println(interval);
    if (timeElapsed > interval) {  
      Serial.println("Stop value has changed");     
      if (off){
        pinMode(stopLight, LOW);
        pinMode(runLight, HIGH);
        Serial.println("STARTED --> Red off and yellow on");
      } else{
        pinMode(stopLight, HIGH);
        pinMode(runLight, LOW);
        Serial.println("STOPPED --> Red on and yellow off");
      }
      stop = !off;
      timeElapsed = 0; // reset the counter to 0 so the counting starts over...
    }
    Serial.print("Elapsed Time (start stop): ");
    Serial.println(timeElapsed);
    delay(100);
  }
}

void setup(){ 
  int pin = 8; //Specify the pin connection (D8)
  esc.attach(pin); //Specify the esc signal pin
  Serial.begin(9600); //Setup input/output screen
  pinMode(JoyStick_Z, INPUT); 
  // LEDs //
  pinMode(stopLight, OUTPUT);
  pinMode(runLight, OUTPUT);
  
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
  pinMode(stopLight, LOW);
  pinMode(runLight, HIGH);
  Serial.println("Red light off and yellow light on");
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
    Serial.println("----- STOP IS FALSE -----");
    if (z == 1){ // If pressed stop
      Serial.println("----- STOP IS FALSE & Z = 1 -----");
      setSpeedAll(1000);
      int success = toggleOnOff(false); // Not already on stop (stop is currently false)
      if (success){
        stop = true;
      }
    } else{ // If not pressed
      Serial.println("----- STOP IS FALSE & Z = 0 -----");
      val = map(x, 0, 1023, 1150, 2000);
      setSpeedAll(val);
      Serial.print("MAPPED VALUE: ");
      Serial.println(val);
      Serial.print("X: ");
      Serial.print(x);
      Serial.print(", Y: ");
      Serial.print(y);
      Serial.print(", Z: ");
      Serial.println(z);
    }
  } else{ // If stop was started
    Serial.println("----- STOP IS TRUE -----");
    setSpeedAll(val);
    int success = toggleOnOff(true); // Stop is currently true
    if (success){
      stop = false;
    }
  }
  delay(3000);
}


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

/*RAMP UP AND RAMP DOWN
Throttle up and down to configure ESC (5 secods to throttle up and 5 seconds to throttle down - can change the delay to change the throttle up and down times)
for (int i = 1000; i <= 2000; i++){ //Throttle up
  esc.writeMicroseconds(i);
}
  Serial.print("RAMP UP: ");
  Serial.println(i);
  delay(5);
}
delay(20);
for (int i = 2000; i >= 1000; i--){ //Throttle down
  esc.writeMicroseconds(i);
  Serial.print("RAMP DOWN: ");
  Serial.println(i);
  delay(5);
}

void loop() 
{
  int x,y,z;
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);
  z=digitalRead(JoyStick_Z);
  if (z == 1){
    Serial.print("Pressed: ");
  } else{
    Serial.print("Depressed: ");
  }
  if ((x < 525 && x > 500) && (y < 525 && y > 500)){
    Serial.println("Center");
  } else if (x >= 525){ 
    if (y >= 525){ 
      Serial.println("South - East");
    } else if (y <= 500){ 
      Serial.println("North - East");
    } else{ 
      Serial.println("East");
    }
  } else if (x <= 500){ 
    if (y >= 525){
      Serial.println("South - West");
    } else if (y <= 500){
      Serial.println("North - West");
    } else{ 
      Serial.println("West");
    }
  } else{ 
    if (y >= 525){ 
      Serial.println("South");
    } else if (y <= 500){ 
      Serial.println("North");
    }
  }
  delay(1000);
}
*/


/*int val = 10;//Can change this to any number between 0 and 1000
val = map(val, 0, 1023, 1000, 2000); //converts inputed value (0-1023) to ouput value for ESC (1000-2000)
esc.writeMicroseconds(val);
delay(5000);//run for 5 seconds*/  
