import socket
import threading

def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', 5000))
    server.listen(5) 
    print("Server listening on port 5000")

    while True:
        client_socket, addr = server.accept()
        print(f"Accepted connection from {addr}")
        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

def handle_client(client_socket):
    try:
        while True:
            message = client_socket.recv(1024).decode()
            if message == "HELLO":
                client_socket.send("Hola!".encode())
            elif message.startswith("FILE_TRANSFER"):
                filename = message.split()[1]
                try:
                    with open(filename, 'rb') as file:
                        data = file.read()
                        client_socket.sendall(data)
                    print(f"Sent file: {filename}")
                except FileNotFoundError:
                    client_socket.send("Error: File not found.".encode())
            elif message.startswith("CALCULATE"):
                expression = message[len("CALCULATE "):]
                try:
                    result = eval(expression)
                    client_socket.send(f"Result: {result}".encode())
                except Exception as e:
                    client_socket.send(f"Error: {str(e)}".encode())
            elif message == "EXIT":
                print("Client disconnected.")
                break           
            else:
                client_socket.send("Unknown command.".encode())
    except Exception as e:
        print(f"An error occurred: {str(e)}")
    finally:
        client_socket.close()

if __name__ == "__main__":
    start_server()
