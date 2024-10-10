import socket

host = '127.0.0.1'
port = 12345

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host, port))
    s.listen()
    
    while True:
        conn, addr = s.accept()
        with conn:
            data = conn.recv(1024).decode()
            print(f"Received: {data}")
            
            words = data.split()
            inverted = []
            for word in words:
                if any(vowel in word.lower() for vowel in 'aeiou'):
                    inverted.append(word[::-1])
                else:
                    inverted.append(word)
            inverted_sentence = ' '.join(inverted)
            
            print(f"Sending: {inverted_sentence}")
            conn.sendall(inverted_sentence.encode())
