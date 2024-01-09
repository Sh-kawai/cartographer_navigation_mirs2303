import rospy
from std_msgs.msg import String
import socket

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
        
        sock_pub.publish(msg)

if __name__ == "__main__":
    try:
        main()
    except rospy.ROSInterruptException:
        pass