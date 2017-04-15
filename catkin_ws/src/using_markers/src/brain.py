#!/usr/bin/env python

###############################################################################
#                           The Brain of Our Robots                           #
###############################################################################
import rospy

from robot_interface import RobotInterface
from shared_code import *

GameStates = enum('INIT', 'PLAY')

def role_move_left(robot):
        robot.goto_xy_pos(10, 0)

def role_move_right(robot):
        robot.goto_xy_pos(0, 0)

def state_operator(game_state):
        #TODO: This is temporary code
        r1 = RobotInterface.all_instances[MarkerID.RED]

        #Set an initial role function on game start
        if game_state == GameStates.INIT:
                r1.role_fn = lambda: role_move_left(r1)
        elif game_state == GameStates.PLAY:
                #Set roles accordingly during game play
                r1_x, _, _ = r1.call_for_cur_pos()
                if r1_x > 9:
                        r1.role_fn = lambda: role_move_right(r1)
                elif r1_x < 1:
                        r1.role_fn = lambda: role_move_left(r1)

def brain():
        try:
		#Initialize the communication interface for our robots
		RobotInterface.initialize_coms()
		
		#Instantiate robots
		#TODO: Introduce more intelligence here
		r1 = RobotInterface(MarkerID.RED)
                ball = RobotInterface(MarkerID.BALL)

                #Initialize the states and roles
                state_operator(GameStates.INIT)
		
		#Set loop rate
		rate = rospy.Rate(RATE)

		#Main loop
		while not rospy.is_shutdown():
                        #Determine if new roles should take effect upon the robots
                        state_operator(GameStates.PLAY)

                        for inst in RobotInterface.all_instances.values():
                                #TODO: Separate robot interfaces into different classes
                                # One for our robots and one for other objects/robots
                                if inst.id <= MarkerID.PURPLE:
                                        inst.role_fn()
                                        inst.spin()

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

