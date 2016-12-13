#include <Servo.h>
#include "AS5145.h"

#define DELTA_T_MS 10
#define ENCODER_MAX_TICS 4096

unsigned long time_us_now;
unsigned long time_us_last;
unsigned long time_us_duration;


AS5145 myAS5145(21,22,20,23); // data, clock, chip select, program input.
long step = 0;

Servo myservo;  // create servo object to control a servo

const uint8_t LED = 13; //red led
boolean led_status = false;

long ticks_last = 0;
long ticks_now = 0;
long delta_ticks = 0;

float angle = 0;
float angular_vel = 0;

int val;    // variable to read the value from the analog pin

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  myservo.attach(17);  // attaches the servo on pin 9 to the servo object
  Serial.begin(115200);
}

void loop() {

  led_status = !led_status;
  digitalWrite(LED, led_status);  // LED blinking

  // Serial.print(++step);

  val = 160;     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  
  ticks_last = ticks_now;
  time_us_last = time_us_now;
  ticks_now = getEncoder();
  time_us_now =  micros();
  time_us_duration = time_us_now - time_us_last;

  // Serial.print("\t");
  // Serial.print(time_us_now); 

  // Serial.print("\t");
  // Serial.print(time_us_last);

  // Serial.print("\t");
  // Serial.print(time_us_duration);

  // Serial.print("\t");
  // Serial.print(ticks_now);
  // Serial.print("\t");
  // Serial.print((ticks_now* 360)/4096);  
  // Serial.print("\t");
  // Serial.print(ticks_last);

  delta_ticks = ticks_now - ticks_last;

  if (abs(delta_ticks)>(ENCODER_MAX_TICS/2)) {
    // delta_ticks = ENCODER_MAX_TICS-delta_ticks;
    if(ticks_now>ticks_last) delta_ticks = ENCODER_MAX_TICS-delta_ticks;
                        else delta_ticks = ENCODER_MAX_TICS+delta_ticks;
  }
  
  // Encoder tics
  // Serial.print("\t");
  // Serial.print(delta_ticks); 

  // Convert tics to degree per second
  angle = ((float)ticks_now* 360)/ENCODER_MAX_TICS;

  // Serial.print("\t");
  Serial.print(angle); 

  angular_vel = ((float)delta_ticks* 360)/ENCODER_MAX_TICS;
  angular_vel = angular_vel * 1000000 / time_us_duration;

  // Serial.print("\t");
  // Serial.print(angular_vel); 

  // // Print rps
  // Serial.print("\t");
  // Serial.print(angular_vel/360);   


  delay(5);                           // waits for the servo to get there
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
  //value = myAS5145.encoder_degrees();
  //Serial.print("measured degrees: ");
  // Serial.print(value);
  // Serial.print("\t");
  // Serial.print((value* 360)/4096);

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
