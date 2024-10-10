import socket

host = '127.0.0.1'
port = 12345
while True:


	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	    s.connect((host, port))
	    message = input("Enter a sentence: ")
	    s.sendall(message.encode())
    
	    data = s.recv(1024).decode()
	    print(f"Received from server: {data}")
    
	    words = data.split()
	    final_result = []
	    for word in words:
	        if not any(vowel in word.lower() for vowel in 'aeiou'):
	            final_result.append(word[::-1])
	        else:
	            final_result.append(word)
	    final_sentence = ' '.join(final_result)
	    
	    print(f"Final result: {final_sentence}")
