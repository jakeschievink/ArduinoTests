import serial, time
def getCurTime(): 
        return time.strftime("%H") + ":" + time.strftime("%M");
PORT = "/dev/ttyUSB0"
ser = serial.Serial(PORT, baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=1)
while True:
        data = ser.readlines()
        if(len(data) > 1):
                print(data[0])
       
