#include <programming_3/bug0.h>
#include <programming_3/math.h>

//Flag para o sensor frontal
int flag = 0;

// Velocity gains
float v_gain = 0.2;
float w_gain = 0.6;

namespace bug{
    /**
    *  Empty constructor
    */
    Bug0::Bug0(){
        // Reserve memory space for 3 sonars.
        for(int i=0; i<2; i++){
            sonarArray.push_back(0);    
        }
        
        
    }

    /**
    *  Empty destructor
    */
    Bug0::~Bug0(){;}
    
    /**
    * Go to Point: Computes desired twist that takes the robot towards the goal point. 
    */
    void Bug0::goToPoint(void){
	
    }
    
    
    /**
    * Wall Following function: Computes desired twist that allows robot circum-navagiating a wall/obstacle.
    */
    void Bug0::wallFollower(void){
	
    }
    
    /**
    * Bug Manager: Decides which sub-routine shall be called.
    */
    void Bug0::bugManager(void){
        // Static variables hold values
        static int state = 0; 
        static double shortestDistanceToGoal = 0;
        
        // Compute current distance in respect to the final goal 
        double distanceToGoal = math::distance2D(this->odometry.pose.pose.position, this->goal);
        // Compute current distance in respect to last hit point
        double distanceToH_in = math::distance2D(this->odometry.pose.pose.position, this->h_in);
        // Compute current distance in respect to last leaving point
        double distanceToH_out = math::distance2D(this->odometry.pose.pose.position, this->h_out);
        
        std::cout << "state: " << state << std::endl;
/*        std::cout << "distance to goal: " << distanceToGoal << std::endl;
        std::cout << "distance to hin: " << distanceToH_in << std::endl;
        std::cout << "distance to hout: " << distanceToH_out << std::endl;*/
        
        switch (state){
            // State 0: Nothing to do.
            case 0: //Reseta a flag do sensor frontal
                    flag=0;
                    if (distanceToGoal > 0.1){ // Robot is far from the goal
                        // Change to "Go to point" state.
                        state = 1;
                    }
                    break;
                
            // State 1: Obstacle free, pursue the goal!
            case 1: // Move toward the goal.
                    this->goToPoint(); 
                    // Did the robot reach the goal?
                    // if (distanceToGoal < 0.05){
                    if (distanceToGoal < 0.1){  
                        // Change to "resting" state.
                        this->twist.linear.x = 0;
                        this->twist.angular.z = 0;
                        state = 0;
                    }
		                // Did the robot detected an obstacle in front of it?
		                else if (this->sonarArray[FRONT_SONAR] > 0 && this->sonarArray[FRONT_SONAR] < 0.8){
                        // Save hit IN point.
                        //h_in = odometry.pose.pose.position;
                        // Change to "obstacle detected" state.
                        state = 2;
                    }
                    break;
            
            
                
            // State 2: Take the robot back to the closest point in respect to final goal
            case 2: // Follow the wall.
                    this->wallFollower();
	                  // No more obstacles
			              if (this->sonarArray[FRONT_SONAR] == 0 &&
			                  this->sonarArray[LEFT_SONAR] == 0 &&
			                  this->sonarArray[RIGHT_SONAR] == 0)
			              {
			                  // Back to "goToPoint" task
			                  ROS_INFO("State 1");
			                  state = 1;
			              }
                    break;
                                        
        } 
        
    }
    
} // closing bug namespace
