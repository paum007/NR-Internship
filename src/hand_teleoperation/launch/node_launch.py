import os
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    return LaunchDescription([

        Node(
            package='hand_teleoperation',
            executable='delay_pub',
            name='delay_pub'
        ),

        # Node(
        #     package='hand_teleoperation',
        #     executable='mediapipe_node',
        #     name='mediapipe_node'
        # )
    ])