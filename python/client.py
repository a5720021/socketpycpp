import socket 
port = 8080
host = "192.168.1.38"  # ip target ,eg ip 's raspberry pi 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
    message = input('Enter your input : ')
    s.sendto(message.encode(), (host, port))
