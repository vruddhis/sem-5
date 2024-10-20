import socket
import random
import time


host = '127.0.0.1'
port = 10000

cs=socket.socket()
cs.connect((host, port))

print("Connection established")

print()
n = int(input("Enter number of frames to send: "))

timeout = float(input("Enter timeout amount in seconds: "))

frames = [f'F{i}' for i in range(n)]
avg_time = (timeout/2 + timeout) / 2
std_dev_time = timeout/4
recv_ack = 0


def display(m=None):
    print()
    for f in frames:
        print(f,end='\t')
    print()
    if(m!=None):
        print('\t'*m + 'Recv')
    print()

display()


while(recv_ack<n):
    while(True):
        print(f'\nSent {frames[recv_ack]}')
        t = abs(random.normalvariate(avg_time, std_dev_time))
        time.sleep(t)
        if(t>timeout):
            print(f'Didn\'t receive ACK within  {timeout} seconds. Resending...')
        else:
            break

    sent_message = frames[recv_ack].encode()
    cs.send(sent_message)
    display(recv_ack)
    x = cs.recv(1024)
    recv_message = x.decode()
    print(f'Received {recv_message} after {t} seconds')
    recv_ack = recv_ack + 1

cs.send('$'.encode())

x = cs.recv(1024)
recv_message = x.decode()
if(recv_message=='$'):
    cs.close()