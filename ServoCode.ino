
#include <Servo.h> 
 
Servo servo1; // initialize servo objects
Servo servo2; 
Servo servo3; 
Servo servo4;
Servo servo5; 
int servo1Pin = 9; // initialize servo pin numbers
int servo2Pin = 10;
int servo3Pin = 11;
int servo4Pin = 12;
int servo5Pin = 13; 
 
int closed = 0;    // open and closed positions in degrees
int open = 180;

int level1 = 100; //altitude levels where different hatches open (currently placeholder values)
int level2 = 200;
int level3 = 300;
int level4 = 400;
int level5 = 500;
int level6 = 600;

float P0 = 1; // ground altitude (measure with bmp280 first)

void setup() 
{ 
  servo1.attach(servo1Pin);  // attaches servos to servo pins
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  
  servo1.write(closed);  // ensures all hatches closed, all servos in closed position
  servo2.write(closed);
  servo3.write(closed);
  servo4.write(closed);
  servo5.write(closed);
} 
 
void loop() 
{ 
  


  if (altitude >= level1) { //opening hatches at different levels, open servo1 at level 1
    servo1.write(open);
  }
  if (altitude >= level2) { // close servo1 at level 2, open servo2 
    servo1.write(closed);
    servo2.write(open);
  }
  if (altitude >= level3) { // close servo2 at level 3, open servo3
    servo2.write(closed);
    servo3.write(open);
  }
  if (altitude >= level4) { // close servo3 at level 4, open servo4
    servo3.write(closed);
    servo4.write(open);
  }
  if (altitude >= level5) { // close servo4 at level 5, open servo5
    servo4.write(closed);
    servo5.write(open);
  }
  if (altitude >= level6) { // close servo5 at level 6
    servo5.write(closed);
  }
} 
*/ */
