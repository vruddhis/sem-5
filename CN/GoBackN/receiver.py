import socket
import random
host = "127.0.0.1"
port = 10000
ss = socket.socket()
ss.bind((host, port))
ss.listen()
print("Established connection")
conn, address = ss.accept()
while True:
    got = (conn.recv(1024)).decode()
    if got=="":
        break
    print("Got frame", got[-1])
    i = int(got[-1])
    ack = str(i + 1)
    if random.randint(0, 1) == 1:
        print("Sending", ack)
        conn.send(ack.encode())
conn.close()