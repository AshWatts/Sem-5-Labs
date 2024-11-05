import socket

def receive_file(host='localhost', port=12345, filename='received_test.txt'):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    sock.sendto(b'REQUEST', (host, port))
    
    with open(filename, 'wb') as file:
        print("Receiving file...")
        while True:
            data, addr = sock.recvfrom(1024)
            if not data:
                break
            file.write(data)

    print(f"File received and saved as {filename}.")
    sock.close()

if __name__ == '__main__':
    receive_file()
