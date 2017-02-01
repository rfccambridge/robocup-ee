
###############################################################################
#                     Define Some Commonly Used Constants                     #
###############################################################################

RATE = 100
DT = 1.0 / RATE

MARKER_COMMAND_TOPIC = "messenger_set_pos"
MARKER_POS_SERVER = "service_get_pos"

#A convenience enum-like object creator
def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    return type('Enum', (), enums)

#TODO: uncomment and check if this works
#Instantiate the ID's of all of the markers in play
MarkerID = enum('RED', 'ORANGE', 'YELLOW', 'GREEN', 'BLUE', 'PURPLE', 'BALL')

