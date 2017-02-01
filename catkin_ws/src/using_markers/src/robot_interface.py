
###############################################################################
#                     The Interface Layer For the Markers                     #
###############################################################################

import rospy

from shared_code import *
from using_markers.srv import *
from using_markers.msg import *

class RobotInterface:
    #Instantiate the variables to be used for communication
    client_get_pos = None
    publisher_set_vels = None

		# Calls the game server to retrieve the current position
		# Outputs in `ret_cur_pos` as cur_x, cur_y tuple
    def call_for_cur_pos(self):		
    	# Request the robot's position with ID of `id`
    	# Send this request via the `client_get_pos`
      resp = RobotInterface.client_get_pos(self.id)
      print "The marker's pos is " + str(resp.pos_x) + " " + str(resp.pos_y) 
      return resp.pos_x, resp.pos_y

    #Calculates the xy velocities of the robot given its current position and a desired destination
    # using a PID controller implementation
    def pid_calc_vels(self):        
        #Constant scaling factors
        K_P = 0.5
        K_I = 0.1
        K_D = 0.1
    
        #Error terms    
        error_x = error_d_x = 0.0
        error_y = error_d_y = 0.0
        
        #Commanded velocities
        vel_x = vel_y = 0.0
        
        #TODO: Make sure `self.call_for_cur_pos` throws an exception on error
        cur_x, cur_y = self.call_for_cur_pos()            

        error_x = self.cmd_x_pos - cur_x
        self.error_i_x += error_x * DT
        error_d_x = error_x / DT
        
        error_y = self.cmd_y_pos - cur_y
        self.error_i_y += error_y * DT
        error_d_y = error_y / DT
        
        #Controller output (velocity)
        vel_x = K_P * error_x + K_I * self.error_i_x + K_D * error_d_x
        vel_y = K_P * error_y + K_I * self.error_i_y + K_D * error_d_y
        
        #Ensure that the robot does not try to achieve some crazy bat-shit speeds
        if vel_x > 10.0:
            vel_x = 10.0
        elif vel_x < -10.0:
            vel_x = -10.0

        if vel_y > 10.0:
            vel_y = 10.0
        elif vel_y < -10.0:
            vel_y = -10.0
            
        #Store the controller outputs in the controller
        return vel_x, vel_y

    #!!!TODO
    #!!!TODO: Enclose the commands from the controller better
    #!!!TODO
    def goto_xy_pos(self, x, y):
        self.cmd_x_pos = x
        self.cmd_y_pos = y
        
        #Reset the error counters for the PID controller
        self.error_i_x = self.error_i_y = 0;

    #Operate the PID and send the output messages
    def spin(self):
        print "spinning!"
        #Get velocities (assume it doesn't fail)
        vel_x, vel_y = self.pid_calc_vels()
      
        #Create a message to publish new velocities 
        msg = speedCommand()

        #Set 'markerID' to 'id'
        msg.markerID = self.id

        #Set the wheel speeds to velocities calculated by 'pid_calc_vels'
	      #!!!TODO
				#!!!TODO: Need to calculate individual wheel speeds based on robot speed from 'pid_calc_vels'
				# wheel_vel_x = vel_x - w*wheel_pos_y
				# wheel_vel_y = vel_y + w*wheel_pos_x
				#Where vel_x and vel_y are robot velocities, wheel_pos_x and wheel_pos_y are the wheel positions relative to the robot, w is the 					angular velocity to rotate the robot
				#!!!TODO
        msg.speed0 = msg.speed2 = vel_x
        msg.speed1 = msg.speed3 = vel_y

        #Send the message to 'MARKER_COMMAND_TOPIC'
        RobotInterface.publisher_set_vels.publish(msg)

    #TODO
    #TODO: Figure out how to specify the message types!
    #TODO
    #Initializes the communication interfaces
    @classmethod
    def initialize_coms(cls):
				#Block until the service becomes available
        rospy.wait_for_service(MARKER_POS_SERVER)
        cls.client_get_pos = rospy.ServiceProxy(MARKER_POS_SERVER, markerPosSrv, persistent=True)

        #TODO: Find a way to test if the publisher is already online!
        #TODO: Make this publish float64 instead, as per what the pose.position variables are spec'd to
        cls.publisher_set_vels = rospy.Publisher(MARKER_COMMAND_TOPIC, speedCommand, queue_size=10)
        

    def __init__(self, _id):
        #!!!TODO
        #!!!TODO: Enclose the commands from the controller better
        #!!!TODO
        self.cmd_x_pos = self.cmd_y_pos = 0
        self.error_i_x = self.error_i_y = 0

        #Instantiate various variables and record initial values
        self.id = _id

    def __del__(self):
        RobotInterface.client_get_pos.close()
        RobotInterface.publisher_set_vels.unregister()
