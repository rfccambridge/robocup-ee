#!/usr/bin/env python

###############################################################################
#                           The Brain of Our Robots                           #
###############################################################################
import rospy

from robot_interface import RobotInterface
from shared_code import *

def brain():
	try:
		#Initialize the communication interface for our robots
		RobotInterface.initialize_coms()
		if not RobotInterface.client_get_pos:
			print "Failed!"
		
		#Instantiate robots
		#TODO: Introduce more intelligence here
		r1 = RobotInterface(MarkerID.RED)
		r1.goto_xy_pos(10,10)
		
		# set loop rate
		rate = rospy.Rate(RATE)

		#Main loop
		while not rospy.is_shutdown():
			r1.spin()
			rate.sleep()

		#Catch Service related exception
	except rospy.service.ServiceException:
		print "Service Exception"
		#The connection was broken, retry connecting and running the `main_loop`
		brain()

	except Exception as e: #Handle all other exceptions more strictly
		print "Fatal exception encountered:", str(e)
		return #Exit on error
    
def main():
	rospy.init_node('command_publisher', anonymous=True)
	#Run the main loop of the brain
	brain()

if __name__ == '__main__':
	main()

