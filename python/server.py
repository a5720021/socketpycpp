import socket
import sys
import hashlib

port = 8089 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
# Accept UDP datagrams, on the given port, from any sender 
s.bind(("", port))
print ("waiting on port:", port)

namefile,addr = s.recvfrom(16)
print("Name file :", namefile)
f3 = open(namefile,'ab') # Open in binar
while (True):
    check_Sum,addr = s.recvfrom(1024)
    f3.write(check_Sum)
    f3.flush()
    if(s.settimeout(2)):
        print("successfully")
f3.close()
s.close()

    
