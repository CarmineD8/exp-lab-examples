#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;


void turtleCallback (const turtlesim::Pose::ConstPtr& msg){
	ROS_INFO("Subscriber, %f, %f, %f", msg->x, msg->y, msg->theta);

	geometry_msgs::Twist vel;
	vel.angular.z = 0.1;
	pub.publish(vel);

} 



int main (int argc, char **argv){
	ros::init(argc,argv,"example");
	ros::NodeHandle nh;
	
	pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);
	ros::Subscriber sub = nh.subscribe("/turtle1/pose",1,turtleCallback);
	ros::spin();
	return 0;
}


