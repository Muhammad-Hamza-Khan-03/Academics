import socket
    
for pings in range(10):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.settimeout(1.0)
    roll = input("Roll Number YY-AAAA-CI ")
    message = bytes(roll, 'utf-8')
    addr = ("127.0.0.1", 12000)

    print(message)
    client_socket.sendto(message, addr)
    try:
        data, server = client_socket.recvfrom(1024)
        data = data.decode('utf-8')
      #  for i in range(0,len(data)):
        #	print(i,data[i])
    except socket.timeout:
        print('REQUEST TIMED OUT')
