import socket
import time

bucket_capacity = 10  
rate_per_second = 2    
bucket = 0           

def process_request(data):
    print(f"Processing request: {data}")


server_socket = socket.socket()
server_socket.bind(('localhost', 8080))
server_socket.listen(5)
print("Server is listening on port 8080...")

last_check_time = time.time()

while True:
    client_socket, addr = server_socket.accept()
    print(f"Connection from {addr}")

    while True:
        
        data = client_socket.recv(1024).decode()

        if not data:
            break  

        
        current_time = time.time()
        time_elapsed = current_time - last_check_time

        
        leaked_requests = int(time_elapsed * rate_per_second)
        if leaked_requests > 0:
            bucket = max(0, bucket - leaked_requests)
            last_check_time = current_time
        
        if bucket < bucket_capacity:
            process_request(data)
            bucket += 1  
        else:
            print("Bucket full! Dropping request.")

    client_socket.close()
