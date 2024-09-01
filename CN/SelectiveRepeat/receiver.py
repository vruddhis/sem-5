import socket
import random

host = "127.0.0.1"
port = 10000

ss = socket.socket()
ss.bind((host, port))
ss.listen()
print("Established connection")

conn, address = ss.accept()

n = int(conn.recv(1024).decode())
print(n)
received = [0] * n

while True:
    got = conn.recv(1024).decode()
    if not got:
        break

    frame_number = int(got.split(",")[1])
    print("Got frame", frame_number)

    if received[frame_number] == 0:
        received[frame_number] = 1
        ack = str(frame_number + 1)
        print("Frame", frame_number, "received correctly. Sending ACK", ack)
    else:
        print("Duplicate frame", frame_number)
        ack_list = [str(i + 1) for i in range(frame_number, n) if received[i]]
        ack = ",".join(ack_list)
        print("Resending ACKs for frames", ack_list)

    if random.randint(0, 1) == 1:
        conn.send(ack.encode())
        print("Sent ACK", ack)
    else:
        print("Simulated ACK loss")

conn.close()
