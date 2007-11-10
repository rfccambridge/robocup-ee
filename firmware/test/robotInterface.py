import serial
ser = 0#the serialclass connection deally
header = '\\H'
footer = '\\E'

#sets up the serial port for connecting to the robot
def setupBot(port = 'COM3'):
    ser = serial.Serial(port)  #open first serial port
    print 'port used: ', ser.portstr       #check which port was realy used



def closeBot():
    ser.close()

def printAll():
    for i in range(0, 256):
        print i, chr(i)
