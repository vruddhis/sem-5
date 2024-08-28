import socket
import time
import select
host = "127.0.0.1"
port = 10000
cs = socket.socket()
cs.connect((host, port))
cs.settimeout(2)
x = input("Enter string")
n = len(x)
i = 0
timeout = 10
lost = []
while i < n:
    start = time.time()
    while time.time()-start < timeout and i < n:
        cs.send((x[i] + "," + str(i)).encode())
        try:
            ack = cs.recv(1024).decode()
        
            if int(ack) == i + 1:
                print("Received ACK" + ack)
        except:
            lost.append(i)
        i += 1
    
        time.sleep(1)
    if len(lost) == 0:
        print("Nothing was lost")
    else:
        print("Something was lost. Starting from index", lost[0])
        i = lost[0]
        lost = []
print("Full message transmitted")
cs.close()