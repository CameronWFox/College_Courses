import socket
import sys

HOST, PORT = "10.8.2.198", 8082

# Create a socket (SOCK_STREAM means a TCP socket)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to server and send data
    sock.connect((HOST, PORT))

    while True:
        # Receive data from the server and shut down
        received = sock.recv(1024)
        print "Received: {}".format(received)
        
        data = raw_input(">")
        sock.sendall(data + "\n")
        
        print "Sent:     {}".format(data)

        if data.startswith("bye"):
            break
finally:
    pass

sock.close()
