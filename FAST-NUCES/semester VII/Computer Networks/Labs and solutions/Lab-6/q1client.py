import socket
    
while 1:
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.settimeout(1.0)
    roll = input("Enter ID: ")
    if(roll >str(9) and roll <str(0)):
    
    	print("Invalid")
    	break;
    
    msg = "Hello I am Client my Id is"+roll
    message = bytes(roll, 'utf-8')
    addr = ("127.0.0.1", 12000)

    
    print(msg)
    client_socket.sendto(message, addr)
    try:
        data, server = client_socket.recvfrom(1024)
        data = data.decode('utf-8')
        
    except socket.timeout:
        print('Enter Next request')
