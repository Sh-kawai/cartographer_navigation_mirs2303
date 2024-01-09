import rospy
from std_msgs.msg import String
from geometry_msgs.msg import PoseStamped
import socket

def process(msg):
    if msg == "NAV":
        #rospy.init_node("goal_publisher", anonymous=True)
        
        goal_msg = PoseStamped()
        goal_msg.header.frame_id = "map"
        goal_msg.pose.position.x = 0.0
        goal_msg.pose.position.y = 0.0
        goal_msg.port.orientation.w = 0.0
        
        goal_pub = rospy.Publisher("/move_base_simple/goal", PoseStamped, queue_size=10)
        goal_pub.publish(goal_msg)

def main():
    rospy.init_node('socket_reciever', anonymous=True)
    sock_pub = rospy.Publisher("socket_receive", String, queue_size=10)
    
    host = ""
    port = 0
    
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))
    rospy.logingo("success connection")
    
    while not rospy.is_shutdown():
        msg = client.recv(4096).decode()
        rospy.loginfo("sock recv: %s", msg)
        
        #process(msg)
        
        sock_pub.publish(msg)

if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass