int JoyStick_X = 0; //x
int JoyStick_Y = 1; //y
int JoyStick_Z = 3; //key
  void setup() 
{
  pinMode(JoyStick_Z, INPUT); 
  Serial.begin(9600); // 9600 bps
}
void loop() 
{
  int x,y,z;
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);
  z=digitalRead(JoyStick_Z);
  /* Z Direction */
  if (z == 1){
    Serial.print("Pressed: ");
  } else{
    Serial.print("Depressed: ");
  }
  /* X and Y Directions */
  if ((x < 525 && x > 500) && (y < 525 && y > 500)){ /* Center */
    Serial.println("Center");
  } else if (x >= 525){ /* Right */
    if (y >= 525){ /* SE */
      Serial.println("South - East");
    } else if (y <= 500){ /* NE */
      Serial.println("North - East");
    } else{ /* E */
      Serial.println("East");
    }
  } else if (x <= 500){ /* Left */
    if (y >= 525){ /* SW */
      Serial.println("South - West");
    } else if (y <= 500){ /* NW */
      Serial.println("North - West");
    } else{ /* W */
      Serial.println("West");
    }
  } else{ /* Center */
    if (y >= 525){ /* S */
      Serial.println("South");
    } else if (y <= 500){ /* N */
      Serial.println("North");
    }
  }
  delay(1000);
}
