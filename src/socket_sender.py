import rospy
from std_msgs.msg import String
import socket

client = None

def callback(msg):
  client.sendall(msg.encode("UTF-8"))
  rospy.logingo("sock send: %s", msg)

def main():
  global client
  
  rospy.init_node('socket_sender', anonymous=True)
  
  host = ""
  port = 0
  
  client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  client.connect((host, port))
  rospy.logingo("success connection")
  
  sock_sub = rospy.Subscriber("socket_send", String, callback)
  
  rospy.spin()

if __name__ == "__main__":
  try:
      main()
  except rospy.ROSInterruptException:
      pass
  