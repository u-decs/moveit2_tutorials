from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            name="cylinder_sub",
            package="moveit2_tutorials",
            executable="cylinder_sub",
        )
    ])