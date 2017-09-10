#!/usr/bin/env python

from socket import *
import sys

port = 8089
host = "192.168.1.35"  # ip target ,eg ip 's raspberry pi 
s = socket(AF_INET, SOCK_DGRAM)
buf = 32768
addr = (host,port)
f1 = open("Testfile.txt",'rb') # Open in binary
f2 = open("picture.npg",'rb') # Open in binary
f3 = open("Testpdf.pdf",'rb') # Open in binary
f4 = open("voice.m4a",'rb') # Open in binary
f5 = open("video.mp4",'rb') # Open in binary
data = f4.read(buf)

while (data):
    if(s.sendto(data,addr)):
        print("sending ...")
    break
s.close()
f4.close()
