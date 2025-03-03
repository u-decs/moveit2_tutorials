
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/msg/display_robot_state.hpp>
#include <moveit_msgs/msg/display_trajectory.hpp>

#include <moveit_msgs/msg/attached_collision_object.hpp>
#include <moveit_msgs/msg/collision_object.hpp>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <moveit/move_group_interface/move_group_interface.h>

static const rclcpp::Logger LOGGER = rclcpp::get_logger("move_group_interface");


int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
      rclcpp::NodeOptions node_options;

    // Create a ROS 2 node
    auto move_group_interface_node = rclcpp::Node::make_shared("move_group_subscriber", node_options);

      // We spin up a SingleThreadedExecutor for the current state monitor to get information
  // about the robot's state.
//   rclcpp::executors::SingleThreadedExecutor executor;
//   executor.add_node(move_group_interface_node);
//   std::thread([&executor]() { executor.spin(); }).detach();

    // Create a MoveIt MoveGroupInterface for the desired planning group
    moveit::planning_interface::MoveGroupInterface move_group(move_group_interface_node, "ur_manipulator");

    static const std::string PLANNING_GROUP = "ur_manipulator";

    RCLCPP_INFO(LOGGER, "NODE 3 RUNNING!");
    
    // We can print the name of the reference frame for this robot.
    RCLCPP_INFO(LOGGER, "Planning frame: %s", move_group.getPlanningFrame().c_str());

    // We can also print the name of the end-effector link for this group.
    RCLCPP_INFO(LOGGER, "End effector link: %s", move_group.getEndEffectorLink().c_str());


    robot_model_loader::RobotModelLoader robot_model_loader(move_group_interface_node, "robot_description");
    const moveit::core::RobotModelPtr& robot_model = robot_model_loader.getModel();
    // /* Create a RobotState and JointModelGroup to keep track of the current robot pose and planning group*/
    moveit::core::RobotStatePtr robot_state(new moveit::core::RobotState(robot_model));
    const moveit::core::JointModelGroup* joint_model_group = robot_state->getJointModelGroup(PLANNING_GROUP);


    //   move_group.getCurrentState()->

  // Visualization
  // ^^^^^^^^^^^^^
  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools(move_group_interface_node, "base_link", "move_group_tutorial",
                                                      move_group.getRobotModel());
  visual_tools.loadRemoteControl();
  visual_tools.trigger();

  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to start the demo");
  visual_tools.deleteAllMarkers();
    // Create a subscriber with topic name "goal_pose"
    auto subscriber = move_group_interface_node->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>(
        "detected_pose", 10, [&](const geometry_msgs::msg::PoseWithCovarianceStamped::SharedPtr msg) {
            geometry_msgs::msg::PoseWithCovarianceStamped goal_pose_covariance = *msg;

            geometry_msgs::msg::PoseStamped goal_pose;
            goal_pose.header = goal_pose_covariance.header;
            goal_pose.pose = goal_pose_covariance.pose.pose;


    bool publisher_count = false;

    // Check if a new message has been received
    if (move_group_interface_node->count_publishers("detected_pose") > 0)
    {
    // Set the flag to indicate that a message has been received
    publisher_count = true;
    }

    visual_tools.publishAxisLabeled(goal_pose.pose, "pose1");


    while (rclcpp::ok() && !publisher_count)
    {
        // rclcpp::spin_some(move_group_interface_node);



        // Sleep for a small duration to avoid high CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    

    // Set the goal pose for planning
    // moveit::core::RobotState goal_state(move_group.getRobotModel());

    move_group.setPoseTarget(goal_pose);
    move_group.setPlanningTime(10.0);
    move_group.setGoalPositionTolerance(0.01);
    move_group.setGoalOrientationTolerance(3.14);
    // Plan and execute the motion
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool success = (move_group.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);
    visual_tools.deleteAllMarkers();
    // visual_tools.publishText(text_pose, "Joint_Space_Goal", rvt::WHITE, rvt::XLARGE);
    visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);

    if (success)
    {
        
        move_group.execute(my_plan);
        RCLCPP_INFO(LOGGER, "Motion executed successfully!");
    }
    else
    {
        RCLCPP_ERROR(LOGGER, "Failed to plan motion!");
    }
    });

    rclcpp::spin(move_group_interface_node);

    rclcpp::shutdown();

    return 0;

}
