import socket
import os

def send_file(filename, host='localhost', port=12345):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((host, port))

    print(f"Server is listening on {host}:{port}")
    
    while True:
        data, addr = sock.recvfrom(1024)
        if data.decode() == 'REQUEST':
            print(f"Sending file {filename} to {addr}")
            with open(filename, 'rb') as file:
                while (chunk := file.read(1024)):
                    sock.sendto(chunk, addr)
            print("File transfer complete.")
            break

    sock.close()

if __name__ == '__main__':
    send_file('test.txt')
