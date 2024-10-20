import socket
import time

client_socket = socket.socket()
client_socket.connect(('localhost', 8080))

for i in range(20):
    message = f"Request {i+1}"
    print(f"Sending: {message}")
    client_socket.send(message.encode())
    time.sleep(0.1)  

client_socket.close()
