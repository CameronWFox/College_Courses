#!/usr/bin/env python 

""" 
A simple echo server 
""" 

import socket 
import subprocess
host = '' 
port = 8089 
backlog = 5 
size = 1024

serverID = socket.gethostbyname(socket.gethostname())

info = 'SERVER ID:{} port: {}'.format(
    serverID, port)

print info
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.bind((host,port)) 
s.listen(backlog)
done = False

# Loop until client sends 'exit' to server
while not done: 
    client, address = s.accept() 
    data = client.recv(size)
    print "Server received: ", data
    if data == "ls":
        lsOutput = subprocess.check_output("dir",shell=True)
        client.send("Listing Directories " + lsOutput)
    if data: 
        client.send("Server Says... " + data)
    if data == "quit":
        done = True
    #elif data == "dir":
        # read contents of current directory into a string and it back to client 
    client.close()
s.close()
print "Server exiting."

