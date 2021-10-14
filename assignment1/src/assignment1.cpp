#include "ros/ros.h"
#include "nav_msgs/Odometry.h" 
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Point.h"
#include "mysrv/Random.h"

// Defining the publisher globally.
ros::Publisher pub;

// Defining the service globally.
ros::ServiceClient client;
mysrv::Random rand_target;

// Defining the target point in free space.
geometry_msgs::Point T_point;
geometry_msgs::Twist vel;

void subscriberCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    ROS_INFO("Robot position: [%f, %f]", msg->pose.pose.position.x, msg->pose.pose.position.y);

    // Reads the position of robot from the pose.pose.position.x.
    float x = msg->pose.pose.position.x;
    float y = msg->pose.pose.position.y;
    
    // Main logic to check the difference between the robot and the target position. 
    if((T_point.x-x) < 0.1 && (T_point.y-y) < 0.1)
     { 
       // Calls service to obtain a random target. 
       client.call(rand_target);

       // Updates the target position of robot.
       T_point.x = rand_target.response.tx;
       T_point.y = rand_target.response.ty;

       //Prints the target position on terminal.
       ROS_INFO("Target position [%lf, %lf]", T_point.x, T_point.y);
    
     }

    // Sets constant velocities for the robot. 
    int k = 1;
    vel.linear.x = k*(T_point.x - x);
    vel.linear.y = k*(T_point.y - y); 
    // Publishes the velocity
    pub.publish(vel);

}

int main(int argc, char **argv)
{
   // Initializes the node.
   ros::init (argc, argv, "assignment1");

   // Creates a nodehandle instance n.
   ros::NodeHandle n;
   
   // Defines the client to receive random target from the server.
   client = n.serviceClient<mysrv::Random>("/random_target");

   // Defines the publisher node.
   pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    
   // Defines the subscriber node that subscribes to the topic /odom.
   ros::Subscriber sub = n.subscribe("/odom", 1000, subscriberCallback);

   ros::spin();

   return 0;

}


