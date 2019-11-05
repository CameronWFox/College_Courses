#!/usr/bin/env python 

""" 
A simple echo client 
""" 

import socket 

host = '10.1.71.155' 
port = 8089 
size = 1024

done = False
while not done:
    userInput = raw_input()
    if "quit" == userInput:
        done = True
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
    s.connect((host,port))
    s.send(userInput) 
    data = s.recv(size) 
    s.close() 
    print 'Received:', data
