import socket
import time

host = "127.0.0.1"
port = 10000

cs = socket.socket()
cs.connect((host, port))
cs.settimeout(2)

x = input("Enter string: ")
n = len(x)
i = 0
ackn = [0] * n

cs.send(str(n).encode())
print("Sent n")

lost = []
timeout = 5

while i < n:
    start = time.time()

    while time.time() - start < timeout and i < n:
        cs.send((x[i] + "," + str(i)).encode())
        print("Sending", x[i] + "," + str(i))

        try:
            ack = cs.recv(1024).decode()
            arr = ack.split(",")

            for a in arr:
                if a.isdigit() and int(a) - 1 < n:
                    ackn[int(a) - 1] = 1
                    print("Got acknowledgment", a)
            if len(arr) == 0:
                lost.append(i)

        except socket.timeout:
            continue

        i += 1
        time.sleep(1)

    if len(lost) == 0:
        print("All frames received successfully")
        break
    else:
        print("Some ack lost")
        first_lost = lost[0]
        lost = []

        for j in range(first_lost, n):
            if ackn[j] == 1:
                print("Resending acknowledgment for frame", j + 1)
                cs.send((str(j + 1) + ",").encode())
                time.sleep(0.5)

print("Full message transmitted")
cs.close()


