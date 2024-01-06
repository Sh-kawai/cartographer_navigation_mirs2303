import rospy
from std_msgs.msg import String

def main():
    rospy.init_node('ros_socket', anonymous=True)
    sock_pub = rospy.Publisher("socket_receive", String, queue_size=10)

if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass