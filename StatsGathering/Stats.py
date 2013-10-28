import serial, time
def getCurTime(): 
        return time.strftime("%H") + ":" + time.strftime("%M")
PORT = "/dev/ttyUSB1"
ser = serial.Serial(PORT, baudrate=9600, bytesize=8, parity='N', stopbits=1, timeout=1)
while True:
        data = ser.readlines()
        if(len(data) >= 1):
                print(data[0])
                with open("data.txt", "a") as datafile:
                        datafile.write("Time: " + getCurTime() +"\n " + data[0].strip().decode('utf-8') + "\n "+ data[1].strip().decode('utf-8')+"\n\n")
       
