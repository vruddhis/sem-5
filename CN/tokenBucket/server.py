import socket
import time

bucket_capacity = 10
rate_per_second = 2
tokens = bucket_capacity
last_check_time = time.time()

def process_request(data):
    print(f"Processing request: {data}")

server_socket = socket.socket()
server_socket.bind(('localhost', 8080))
server_socket.listen(5)
print("Server is listening on port 8080...")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Connection from {addr}")

    while True:
        data = client_socket.recv(1024).decode()
        if not data:
            break

        current_time = time.time()
        time_elapsed = current_time - last_check_time

        new_tokens = int(time_elapsed * rate_per_second)
        tokens = min(bucket_capacity, tokens + new_tokens)
        last_check_time = current_time

        if tokens > 0:
            process_request(data)
            tokens -= 1
        else:
            print("Not enough tokens! Dropping request.")

    client_socket.close()
