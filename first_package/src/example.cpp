#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "custom_messages/Two.h"
#include "custom_messages/Sum.h"

ros::Publisher pub;
ros::Publisher pub2;


void turtleCallback (const turtlesim::Pose::ConstPtr& msg){
	ROS_INFO("Subscriber, %f, %f, %f", msg->x, msg->y, msg->theta);
	custom_messages::Two two;
	two.a = msg->x;
	two.b = msg->y;
	pub2.publish(two);

} 

bool addCallback (custom_messages::Sum::Request& req, custom_messages::Sum::Response& res){
	res.sum = req.a + req.b;
	geometry_msgs::Twist vel;
	vel.linear.x = req.a;
	vel.angular.z = req.b;
	pub.publish(vel);
	return true;
}



int main (int argc, char **argv){
	ros::init(argc,argv,"example");
	ros::NodeHandle nh;
	
	ros::ServiceClient client = nh.serviceClient<turtlesim::Spawn>("/spawn");
	turtlesim::Spawn srv;
	srv.request.x = 2.0;
	srv.request.y = 2.0;
	srv.request.name = "my_turtle";
	client.call(srv);

	pub = nh.advertise<geometry_msgs::Twist>("/my_turtle/cmd_vel",1);
	pub2 = nh.advertise<custom_messages::Two>("/position",1);
	
	ros::ServiceServer service = nh.advertiseService("/sum", addCallback);

	ros::Subscriber sub = nh.subscribe("/my_turtle/pose",1,turtleCallback);
	ros::spin();
	return 0;
}


