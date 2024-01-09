#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>

ros::Publisher scan_publisher;

void convertScan(const sensor_msgs::LaserScan::ConstPtr& input_scan){
    const float max_angle = 1.570796;
    const float min_angle = -1.570796;

    // new scan data
    sensor_msgs::LaserScan filtered_scan;
    filtered_scan.header = input_scan->header;
    filtered_scan.angle_min = input_scan->angle_min;
    filtered_scan.angle_max = input_scan->angle_max;
    filtered_scan.angle_increment = input_scan->angle_increment;
    filtered_scan.time_increment = input_scan->time_increment;
    filtered_scan.scan_time = input_scan->scan_time;
    filtered_scan.range_min = input_scan->range_min;
    filtered_scan.range_max = input_scan->range_max;

    // filtere data
    int num_ranges = (input_scan->angle_max - input_scan->angle_min) / input_scan->angle_increment;
    filtered_scan.ranges.resize(num_ranges);
    filtered_scan.intensities.resize(num_ranges);

    //printf("increment:%f", input_scan->angle_increment);

    for (int i=0; i < num_ranges; i++){
        float angle = input_scan->angle_min + i * input_scan->angle_increment;
        if(angle > min_angle && angle < max_angle){
            filtered_scan.ranges[i] = std::numeric_limits<float>::infinity();
        } else {
            filtered_scan.ranges[i] = input_scan->ranges[i];
        }
        filtered_scan.intensities[i] = input_scan->intensities[i];
    }

    //publish
    scan_publisher.publish(filtered_scan);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "scan_repair");
    ros::NodeHandle nh;

    scan_publisher = nh.advertise<sensor_msgs::LaserScan>("/scan", 10);
    ros::Subscriber scan_subscriber = nh.subscribe("/scan_raw", 10, convertScan);

    ros::spin();

    return 0;
}