#include <ros.h>
#include <ArduinoHardware.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <nav_msgs/Odometry.h>

ros::NodeHandle nh;
nav_msgs::Odometry odom;
ros::Publisher odom_pub("odom", &odom);

#define SPIN_US 100000 // 100ms

// odom
float x, theta;
float vx, vtheta;
unsigned long curr_time, prev_time;

void odom_init(){
  x = 0.0;
  theta = 0.0;
  vx = 0.0;
  vtheta = 0.0;

  odom.pose.pose.position.x = 0.0;
  odom.pose.pose.position.y = 0.0;
  odom.pose.pose.position.z = 0.0;

  odom.pose.pose.orientation.x = 0.0;
  odom.pose.pose.orientation.y = 0.0;
  odom.pose.pose.orientation.z = 0.0;
  odom.pose.pose.orientation.w = 0.0;

  odom.twist.twist.linear.x = 0.0;
  odom.twist.twist.linear.y = 0.0;
  odom.twist.twist.angular.z = 0.0;

  prev_time = 0;
}

void odom_cal(){
  static float x_prev = 0.0;
  static float theta_prev = 0.0;
  float dx, dtheta;
  
  //x++;
  //theta += 1 * 3.1415 / 180.0;
  
  dx = x - x_prev;
  dtheta = theta - theta_prev;
  
  x_prev = x;
  theta_prev = theta;

  vx = dx / ((curr_time - prev_time) / SPIN_US);
  vtheta = dtheta / ((curr_time - prev_time) / SPIN_US);
}

void setup() {
  // put your setup code here, to run once:
  nh.getHardware()->setBaud(9600);
  nh.advertise(odom_pub); // publisher
  nh.initNode();
  odom_init();
}

void loop() {
  curr_time = micros();
  if((curr_time - prev_time) > SPIN_US){
    // put your main code here, to run repeatedly:
    odom.header.stamp = nh.now();
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
  
    odom_cal();
    
    // now position
    odom.pose.pose.position.x = x;
    odom.pose.pose.orientation = tf::createQuaternionFromYaw(theta); // direction
    // now velocity
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.angular.z = vtheta;
    // odom publish
    odom_pub.publish(&odom);

    Serial.println(x);
    
    prev_time = curr_time;
  }
  
  nh.spinOnce();
  delay(10);
}
