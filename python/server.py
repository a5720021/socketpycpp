import socket 
port = 8089 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) 
# Accept UDP datagrams, on the given port, from any sender 
s.bind(("", port)) 
print ("waiting on port:", port)
while 1:
    # Receive up to 1,024 bytes in a datagram 
    data,addr = s.recvfrom(1024)
    datathai = data.decode("cp874")
    print ("Received:", datathai, "from", addr)
