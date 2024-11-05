import socket

def send_message(client_socket, message):
    try:
        print(f"Sending: {message}")
        client_socket.send(message.encode())
        response = client_socket.recv(1024).decode()
        print(f"Response: {response}")
    except Exception as e:
        print(f"An error occurred: {str(e)}")

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        client.connect(('localhost', 5000))
        print("Connected to the server.")

        send_message(client, "HELLO")

        send_message(client, "FILE_TRANSFER test.txt")

        send_message(client, "CALCULATE 3 + 5")

        send_message(client, "EXIT")

    except Exception as e:
        print(f"An error occurred: {str(e)}")
    finally:
        client.close()

if __name__ == "__main__":
    main()
