import serial
import os 
ser = serial.Serial('/dev/ttyUSB0',9600)
while True:
        motiondetector = ser.readline().strip('\r\n')
        if(motiondetector == '1'):
                print('motion')
                #os.system('mplayer ~/Downloads/laugh.mp3')
        else:
                print("nah")
