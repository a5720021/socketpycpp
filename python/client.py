import socket
port = 8089
host = "192.168.1.35"  # ip target ,eg ip 's raspberry pi 
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
    mesege = input('intput :')
    s.sendto(mesege.encode("cp874"), (host, port))
