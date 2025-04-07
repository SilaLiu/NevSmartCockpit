import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource, XMLLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # 配置参数
    config = {
        'can_interface': LaunchConfiguration('can_interface', default='can0'),
        'server_port': LaunchConfiguration('server_port', default='12345'),
        'use_control_publisher': LaunchConfiguration('use_control_publisher', default='false'),
        'use_feedback_subscriber': LaunchConfiguration('use_feedback_subscriber', default='true')
    }
    
    # 1. CAN总线通信
    can_bridge = IncludeLaunchDescription(
        XMLLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('ros2_socketcan'),
                'launch/socket_can_bridge.launch.xml'
            )
        ),
        launch_arguments={'interface': config['can_interface']}.items()
    )
    
    # 2. NEV驱动核心
    nev_driver = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('pix_nev_driver'),
                'launch/pix_nev_driver_component.launch.py'
            )
        ),
        launch_arguments={'can_interface': config['can_interface']}.items()
    )
    
    # 3. 服务器接口
    server_interface = IncludeLaunchDescription(
        XMLLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory('nev_server_interface'),
                'launch/server.launch.xml'
            )
        ),
        launch_arguments={'port': config['server_port']}.items()
    )
    
    # 4. 可选组件
    control_publisher = ExecuteProcess(
        cmd=['python3', os.path.join(
            get_package_share_directory('nev_server_interface'),
            'scripts/control_publisher.py'
        )],
        output='screen',
        condition=IfCondition(config['use_control_publisher'])
    )
    
    feedback_subscriber = ExecuteProcess(
        cmd=['python3', os.path.join(
            get_package_share_directory('nev_server_interface'),
            'scripts/feedback_subscriber.py'
        )],
        output='screen',
        condition=IfCondition(config['use_feedback_subscriber'])
    )

    return LaunchDescription([
        can_bridge,
        nev_driver,
        server_interface,
        control_publisher,
        feedback_subscriber
    ])