#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  //receive_serial();
  cal_wheel_vel();
  ros_send_odom(); // send linear_x, angular_z;
  delay(100);
}
