import socket
import signal
import sys
import time
from autobahn.twisted.util import sleep
from serial.rfc2217 import DO

s = socket.socket()
host = socket.gethostname()
port = 12345
ret = "OK"

exit_flag = 0 
def main():
    
    signal.signal(signal.SIGINT, sigintHandler)
      
    s.connect((host, port))
    s.send("HPS3D_DevicInit,0\n")
    data = s.recv(2);
    if data != ret:
        print("send HPS3D_DevicInit failed")
        return;
    print("HPS3D_DevicInit")
    
    s.send("HPS3D_SetRunMode,0,2\n")
    print("HPS3D_SetRunMode")
      
    print("Start....")  
    while exit_flag==0:
        data = s.recv(1024)
        print(data)

def sigintHandler(signum, frame):
    exit_flag = 1
    s.send("HPS3D_RemoveDevice All\n")
    data =  s.recv(2);
    while data!= ret: 
        data = s.recv(2);
    
    print("HPS3D_RemoveDevice succeed");
    s.close()
    exit()     
        
if __name__ == "__main__":
    try:
        main()
    finally:
        sys.exit()        
        
        
        
        