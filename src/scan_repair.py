import rospy
import numpy as np
from sensor_msgs.msg import LaserScan

scan_publisher = None

def convert_scan(data):
    global scan_publisher

    ignore_angle_min = -0.523599
    ignore_angle_max = 0.523599

    # 新しいLaserScanメッセージを作成します。
    filtered_scan = LaserScan()
    filtered_scan.header = data.header
    filtered_scan.angle_min = data.angle_min
    filtered_scan.angle_max = data.angle_max
    filtered_scan.angle_increment = data.angle_increment
    filtered_scan.time_increment = data.time_increment
    filtered_scan.scan_time = data.scan_time
    filtered_scan.range_min = data.range_min
    filtered_scan.range_max = data.range_max

    # 無視する範囲のデータを除外します。
    for i, angle in enumerate(np.arange(data.angle_min, data.angle_max, data.angle_increment)):
        if angle > ignore_angle_min and angle < ignore_angle_max:
            filtered_scan.ranges.append(float('nan'))
        else:
            filtered_scan.ranges.append(data.ranges[i])
            
    # フィルタリング後のデータをパブリッシュします。
    scan_publisher.publish(filtered_scan)


if __name__ == '__main__':
    rospy.init_node('scan_repair', log_level=rospy.DEBUG)

    rospy.Subscriber('/scan', LaserScan, convert_scan)
    scan_publisher = rospy.Publisher('/scan_front', LaserScan, queue_size=10)

    r = rospy.Rate(10)
    while not rospy.is_shutdown():
        r.sleep()