# turtlesim/launch/multisim.launch.py

from launch import LaunchDescription
import launch_ros.actions

def generate_launch_description():
    return LaunchDescription([
        # launch_ros.actions.Node(
        #     namespace= "pid_controller", package='pid_controller', executable='pid_controller', output='screen'),        
        launch_ros.actions.Node(
            namespace= "dummy_sensor", package='dummy_sensor', executable='position_data', output='screen'),
        # launch_ros.actions.Node(
        #     namespace= "dummy_brain", package='dummy_brain', executable='dummy_brain', output='screen'),
    ])