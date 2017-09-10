import socket
import sys
import hashlib

port = 8089 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
# Accept UDP datagrams, on the given port, from any sender 
s.bind(("", port))
#print (hashlib.md5(open("Testfile.txt", 'rb').read()).hexdigest())
print ("waiting on port:", port)

f1 = open("Testfile.txt",'wb') # Open in binary
f2 = open("picture.npg",'wb') # Open in binary
f3 = open("Testpdf.pdf",'wb') # Open in binary
f4 = open("voice.m4a",'wb') # Open in binary
f5 = open("video.mp4",'wb') # Open in binary
check_Sum,addr = s.recvfrom(1024)

while (check_Sum):
    f1.write(check_Sum)
    print ("Received:", check_Sum, "from", addr)
    #correct = hashlib.md5(open('Testfile.txt','rb').read()).hexdigest()
    #print(correct)
    break
f1.close()
s.close()

    
