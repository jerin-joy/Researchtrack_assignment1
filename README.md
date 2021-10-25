# Research Track I - First Assignment

# Done by Jerin Joy (Matricola - 5061530)

# Description of the assignment

The assignment requires controlling a holonomic robot in a 2D space with a simple 2D simulator. The robot needs to reach a random target in the interval (-6.0, 6.0). The target is considered to be reached when the distance between the robot and target is below 0.1. After reaching the target, robot acquires a new random target and the same process is repeated.

For developing the assignment, two ROS nodes are created. 
- The first node calls the service for receiving the random target and to make the robot reach the target.
- The second node acts as a Service Server, by replying to the client with a random target.

All the nodes are developed using CPP.

# Description of the first node  

The first node consists of a ROS Publisher, a ROS Subscriber and a ROS Client. The ROS Publisher which publishes to the topic /cmd_vel which is used to set the robot speed. The ROS Subscriber is subscribed to the topic /odom to know the actual position of the robot. The position of the robot is defined in the topic /odom, by using nav_msgs/Odometry and the x and y coordinates of the robot is retreived by reading the pose.pose.position.x and pose.pose.position.y fields of the message received by the callback respectively. And the ROS Client is used to receive a random target.

# Server: mysrv

The CPP file 'random_target.cpp' for the random target is placed inside the src folder of the Server package mysrv. It contains the source code for generating random integer within a specified range and advertise it to the node /random_target. Inside the srv folder, a service message named Random.srv which uses responses with two integers namely min and max. The request text field is left empty.

# Instructions to set up the Workspace

The following steps is used to prepare the necessary environment and dependencies to run the assignment:

1. Open the command line terminal and navigate to the local workspace using *cd /<name of the ws>(my_ros_ws)/src* command.

2. Clone the remote repository of assignment in your local workspace using the command: *git clone https://github.com/jerin-joy/Researchtrack_assignment1.git*

3. Build the file using *catkin_make* in the root folder of the workspace.

4. Run the command *rospack profile* to read and parse the .xml for each package and provide a complete dependency tree for all packages.

# Instructions to run the Assignment

1. Simulator for the holonomic robot in 2D space can be launched using the command:
```bash
rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world
```

2. Open a new command line terminal, run the command to initialise the node for receiving the random target and make the robot to reach the target:
```bash
rosrun mysrv random_target
```

3. Open a new command line terminal, run the command to run the main node for receiving the random target and make the robot reach the target:
```bash
rosrun assignment1 assignment1
```

4. In a new command line terminal, run the command to view the computational graph:
```bash
rosrun rqt_graph rqt_graph
```
