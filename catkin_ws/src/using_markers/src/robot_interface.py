
###############################################################################
#                     The Interface Layer For the Markers                     #
###############################################################################

import rospy

from shared_code import *
from using_markers.srv import *
from using_markers.msg import *

from heapq import *

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

    def astar(self, start, goal, xdim, ydim, obstacles):
        """Takes a `start` and `goal` tuple of coords, and returns a list of the best path between those points.
        The `obstacles` is a list of lambda functions of two args, (x and y), that tell if a given point
        is valid or encroaches the obstacle."""

        def heuristic(a, b):
            return (b[0] - a[0]) ** 2 + (b[1] - a[1]) ** 2

        neighbors = [(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]

        #Data describing closed points
        close_set = set()
        came_from = {}
        gscore = {start:0}
        fscore = {start:heuristic(start, goal)}
    
        #The open heap of points to test
        oheap = []

        heappush(oheap, (fscore[start], start))
    
        while oheap:

            current = heappop(oheap)[1]

            if current == goal:
                data = []
                while current in came_from:
                    data.insert(0, current)
                    current = came_from[current]
                return data

            close_set.add(current)
            for i, j in neighbors:
                #Build a point to test the path on and a `tentative_g_score` for it
                neighbor = current[0] + i, current[1] + j            
                tentative_g_score = gscore[current] + heuristic(current, neighbor)
            
                #Check if the neighboring point is valid for the path
                if 0 <= neighbor[0] < xdim:
                    if 0 <= neighbor[1] < ydim:                
                        if any(map(lambda fn: fn(neighbor[0], neighbor[1]), obstacles)):   #This is an obstacle
                            continue
                    else:
                        # array bound y walls
                        continue
                else:
                    # array bound x walls
                    continue
                
                if neighbor in close_set and tentative_g_score >= gscore.get(neighbor, 0):
                    continue
                
                #Process this point if the `tentative_g_score` beats what is currently known in the 
                # closed set, or if this point is still unknown
                if tentative_g_score < gscore.get(neighbor, 0) or neighbor not in [i[1] for i in oheap]:
                    came_from[neighbor] = current
                    gscore[neighbor] = tentative_g_score
                    fscore[neighbor] = tentative_g_score + heuristic(neighbor, goal)
                    heappush(oheap, (fscore[neighbor], neighbor))

        #No valid path was found!
        return False

    #!!!TODO
    #!!!TODO: Enclose the commands from the controller better
    #!!!TODO
    def goto_xy_pos(self, x, y):

        cur_x, cur_y = self.call_for_cur_pos()

        #TODO: Figure out granularity of field and obstacle list
        if self.path == []:
            self.path = self.astar((int(cur_x), int(cur_y)), (x, y), 50, 50, [])

            #If the returned list is empty, then we are at our final destination
            if self.path == []:
                return

        threshold = 0.5 #TODO: Figure this out!
        fst_x, fst_y = self.path[0]

        #Check intermediate step thresholds
        if (fst_x - cur_x) < threshold and (fst_y - cur_y) < threshold:
            self.path.pop(0)    #Delete the first element of the list

            #Reset the error counters for the PID controller
            self.error_i_x = self.error_i_y = 0;

        #Set the desired step destination
        self.cmd_x_pos = fst_x
        self.cmd_y_pos = fst_y        

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
        #
        #Where vel_x and vel_y are robot velocities, wheel_pos_x and wheel_pos_y are the wheel 
        # positions relative to the robot, w is the angular velocity to rotate the robot
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
        self.path = []

        #Instantiate various variables and record initial values
        self.id = _id

    def __del__(self):
        RobotInterface.client_get_pos.close()
        RobotInterface.publisher_set_vels.unregister()
