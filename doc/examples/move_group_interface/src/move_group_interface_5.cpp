
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/msg/display_robot_state.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>

#include <moveit_msgs/msg/attached_collision_object.hpp>
#include <moveit_msgs/msg/collision_object.hpp>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <moveit/move_group_interface/move_group_interface.h>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("move_group_subscriber");


int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("goal_pose_publisher");


    // Create a MoveIt MoveGroupInterface for the desired planning group
    moveit::planning_interface::MoveGroupInterface move_group(node, "ur_manipulator");


    // Create publisher for the current pose
    auto pose_pub = node->create_publisher<geometry_msgs::msg::PoseStamped>("current_pose", 10);
    // Create publisher for the random pose
    auto pose_pub_2 = node->create_publisher<geometry_msgs::msg::PoseStamped>("random_pose", 10);
    auto ee_link = move_group.getEndEffectorLink();
    // RCLCPP_INFO(LOGGER,"End effector: %s", move_group.getEndEffectorLink());

  while (rclcpp::ok())
  {

    geometry_msgs::msg::PoseStamped current_pose = move_group.getCurrentPose();
    pose_pub->publish(current_pose);

    geometry_msgs::msg::PoseStamped random_pose = move_group.getRandomPose();
    pose_pub_2->publish(random_pose);

  
  }

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;

}
