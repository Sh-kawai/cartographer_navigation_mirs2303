#include <ros.h>
#include <nav_msgs/Odometry.h>

ros::NodeHandle nh;
ros::Publisher odom_pub("odom", 10);
nav_msgs::Odometry odom;

volatile long encoderValue = 0;

void setup() {
    nh.initNode();
}

void loop() {
    encoderValue = get_enc();

    nav_msgs::Odometry odom;
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";
    odom.pose.pose.position.x = encoderValue;

    odom_pub.publish(&odom);

    nh.spinOnce();
    delay(100);
}

long get_enc(){
    static long a = 0;
    a++;
    if(a > 9999) a = 0;
    return a;
}
