#include <Servo.h>
#include "AS5145.h"

#define DELTA_T_MS 10

AS5145 myAS5145(21,22,20,23); // data, clock, chip select, program input.
long step = 0;

Servo myservo;  // create servo object to control a servo

const uint8_t LED = 13; //red led
boolean led_status = false;

long angle_last = 0;
long angle_now = 0;
long angular_vel = 0;

int val;    // variable to read the value from the analog pin

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  myservo.attach(17);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {

  led_status = !led_status;
  digitalWrite(LED, led_status);  // LED blinking

  val = 90;     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  
  angle_last = angle_now;
  angle_now = getEncoder();

  if (angle_now >= angle_last) {
  	angular_vel = angle_now - angle_last;
  } else {
  	angular_vel = angle_now + 360 - angle_last;
  }
  angular_vel = (angular_vel* 360)/4096;
  angular_vel = angular_vel * DELTA_T_MS;

  Serial.print("\t");
  Serial.print(angular_vel); 


  delay(DELTA_T_MS);                           // waits for the servo to get there
  Serial.println(" ");
}


long getEncoder (void) {
  //Serial.print("Step: ");
  //Serial.println(++step);

  long value;

  // method 1
  value = myAS5145.encoder_value();
  //Serial.print("measured value: ");
  //Serial.print(value);Serial.print("\t");
  value = myAS5145.encoder_degrees();
  //Serial.print("measured degrees: ");
  Serial.print(value);
//   if (myAS5145.encoder_error()>>3)
//   {
// //    if (myAS5145.err_value.DECn) Serial.println("DECn error");
// //    if (myAS5145.err_value.INCn) Serial.println("INCn error");
//     if (myAS5145.err_value.COF) Serial.println("COF error");
//     if (myAS5145.err_value.OCF) Serial.println("OCF error");
//     if (myAS5145.err_value.LIN) Serial.println("out of range");
//   }

  return value;
}
