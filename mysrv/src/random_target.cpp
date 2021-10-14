#include "ros/ros.h"
#include "mysrv/Random.h"


// Function for generating a random number between 2 numbers [M,N]
double randMToN(double M, double N) 
{ 
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;
}

// Function to generate random number between a max and min value and assign to x and y. i.e, in this case -6 and 6.
bool randomTarget (mysrv::Random::Request &req, mysrv::Random::Response &res)
{
   
   res.tx = randMToN(-6.0, 6.0);
   res.ty = randMToN(-6.0, 6.0);
   return true;
}

int main(int argc, char **argv)
{
    // Initialize the node, setup the NodeHandle for handling the communication with the ROS

    ros::init(argc, argv, "random_server");
    ros::NodeHandle n;

    // Define the service 'random_target'
    ros::ServiceServer service= n.advertiseService("/random_target", randomTarget);
    ros::spin();

    return 0;
}
