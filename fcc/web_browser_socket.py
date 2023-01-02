import socket
import sys

server = 'data.pr4e.org'
link = f'http://{server}/romeo.txt'

def main() :
    my_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    my_sock.connect((server, 80))
    cmd = f'GET {link} HTTP/1.0\r\n\r\n'.encode()
    my_sock.send(cmd)

    while True :
        data = my_sock.recv(512)
        if (len(data) < 1) :
            break
        print(data.decode())

    my_sock.close()
    sys.exit()

if __name__ == '__main__' :
    main()

