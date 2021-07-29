#socat -d -d -v pty,rawer,echo=0,link=./reader pty,rawer,echo=0,link=./writer

import serial as sr

ser = sr.Serial('/dev/ttyUSB0')
#ser = sr.Serial('/dev/pts/2')
ser.baudrate = 115200
#ser.port = '/dev/ttyUSB0'
#ser.open()
if not ser.is_open :
    ser.open()
print("OPEN")

while True :
    a = input()
    msg = a +'\r\n'
    ser.write(msg.encode('windows-1251'))
    print(a)
    if a == "quit" :
        break
print("Bye")
