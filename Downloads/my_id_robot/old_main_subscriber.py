import rclpy
from subprocess import call
from rclpy.node import Node
from time import sleep

from std_msgs.msg import String


class MainSubscriber(Node):

    def __init__(self):
        super().__init__('main_subscriber')
        self.subscription = self.create_subscription(
            String,
            'voice',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard "%s"' % msg.data)
        arg_a = '-ven-us+f4'
        arg_b = 'Hello'
        # Turn off the microphone
        call(["pactl", "set-source-mute", "3", "toggle"])
        # Execute espeak using subprocess.run() 
        call(["espeak", "-ven-us+f3", "hello"])
        call(["espeak", "-ven-us+f3", msg.data])
#        sleep(5)
        #Turn on the microphone
        call(["pactl", "set-source-mute", "3", "toggle"])
        

def main(args=None):
    rclpy.init(args=args)

    main_subscriber = MainSubscriber()

    rclpy.spin(main_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    main_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
