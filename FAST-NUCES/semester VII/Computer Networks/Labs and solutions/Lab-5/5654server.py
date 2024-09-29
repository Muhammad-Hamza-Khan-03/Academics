import random
import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind(('', 12000))

roll_lsit =[]
while True:
    rand = random.randint(0, 10)
    message, address = server_socket.recvfrom(1024)
    message = message.decode('utf-8')
    message = message.split('-')
    
    
            
    if('CI' in message[2]):
    	print("Welcome Student,",message)
    	if(isinstance(message,str)):
    		message = bytes(message, 'utf-8')
    	roll_lsit.append(message[1])
    if('CO' in message[2]):
    	if(message[1] in roll_lsit):
    		print("GoodBye Student ",message," Have a nice day.")
    		if(isinstance(message,str)):
    			message =bytes(message, 'utf-8')
    	
    		roll_lsit.remove(message[1])
    elif('CO' in message[2] and message[1] not in roll_lsit):
    		print("You didn’t check in today. Contact System Administrator.")
    #data = message.decode('utf-8')
    print ("printing list:")
    for i in range(0,len(roll_lsit)):
        print(i,roll_lsit[i])
    #server_socket.sendto(roll_lsit, address)
    #print(message)
