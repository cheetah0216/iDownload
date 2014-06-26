import sys
import socket

class Client:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.bufSize = 64*1024

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect( (self.ip, self.port) )

    def recvFiles(self, filename):
        files = open(filename, 'wb')
        while True:
            data = self.sock.recv(self.bufSize)
            if not data:
                break;
            files.write(data)
        files.flush()
        files.close()

    def close(self):
        self.sock.close();


if __name__ == '__main__':
    client = Client('10.0.0.4',2021)
    client.connect()
    client.recvFiles(sys.argv[1])
    client.close()
