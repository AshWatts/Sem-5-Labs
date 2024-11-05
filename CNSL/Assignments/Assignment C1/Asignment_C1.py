import socket

def dns_lookup():
    print("DNS Lookup Tool")
    print("1. Get URL from IP address")
    print("2. Get IP address from URL")
    
    choice = input("Enter your choice (1 or 2): ")
    
    if choice == '1':
        ip_address = input("Enter the IP address: ")
        try:
            url = socket.gethostbyaddr(ip_address)
            print(f"The URL corresponding to {ip_address} is: {url[0]}")
        except socket.herror:
            print("Unable to find the corresponding URL.")
    elif choice == '2':
        url = input("Enter the URL: ")
        try:
            ip_address = socket.gethostbyname(url)
            print(f"The IP address corresponding to {url} is: {ip_address}")
        except socket.gaierror:
            print("Unable to find the corresponding IP address.")
    else:
        print("Invalid choice. Please enter 1 or 2.")

if __name__ == "__main__":
    dns_lookup()