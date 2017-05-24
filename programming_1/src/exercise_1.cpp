#include <stdio.h>

/** include ros libraries  ************/
#include <std_msgs/String.h>
#include <ros/ros.h>

int main(int argc, char **argv)
{
    //***  First: initialize ROS giving it argc, argv and a Name ***


    //*** Second: create a Node  ***


    //*** Third: create a Publisher inside that Node, the publisher is defined by a type, a name and the size of the buffer


    //*** NB: remember of creating a ros::Rate here


    while( ros::ok() )
    {
        //*** Fourth: create a message and put in it some content ***


        //*** Fifth: publish the message


        //*** Sixth: make a ROS_INFO


        //*** Last: remember of spinning and sleeping for a while


    }
}
