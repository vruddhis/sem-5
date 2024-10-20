import socket

host = '127.0.0.1'
port = 10000

ss=socket.socket()
ss.bind((host, port))
ss.listen()

print("Connection established")
conn, addr = ss.accept()

received_frames = []

def display():
    print()
    for f in received_frames:
        print(f,end='\t')
    print()
    print()

recv_message = ''

while(recv_message!='$'):
    x = conn.recv(1024)
    recv_message = x.decode()
    print(f'Received {recv_message}') if recv_message!='$' else print('Received  all the frames')
    y = 'ACK' + recv_message[1:]
    sent_message = y.encode()
    conn.send(sent_message)
    if(recv_message!='$'):
        received_frames.append(recv_message)
    display()

sent_message = '$'.encode()
conn.send(sent_message)
ss.close()