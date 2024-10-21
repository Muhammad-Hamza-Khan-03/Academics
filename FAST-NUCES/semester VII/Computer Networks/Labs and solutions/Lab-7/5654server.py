import socket
import threading

def load_voters():
    voters = {}
    with open("voters_list.txt", "r") as f:
        for line in f:
            name, cnic = line.strip().split('/')
            voters[cnic] = name
    return voters

def load_candidates():
    candidates = {}
    with open("candidates_list.txt", "r") as f:
        for line in f:
            name, symbol = line.strip().split()
            candidates[symbol] = name
    return candidates

def handle_client(conn, addr, voters, candidates):
    print(f"New connection from {addr}")
    while True:
        try:
            
            data = conn.recv(1024).decode('utf-8')
            if not data:
                break
            
            name, cnic, symbol = data.split(',')
            print("Welcome "+name)
            if cnic not in voters:
                response = "Invalid CNIC. You are not registered to vote."
            elif symbol not in candidates:
                response = "Invalid voting symbol. Please try again."
            else:
                response = "Vote cast successfully."
            
            conn.sendall(response.encode('utf-8'))
        except Exception as e:
            print(f"Error: {e}")
            break
    
    print(f"Connection from {addr} closed")
    conn.close()

host = ""
port = 12345

voters = load_voters()
candidates = load_candidates()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host, port))
    s.listen()
    print(f"Server is listening on port {port}")

    while True:
        conn, addr = s.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr, voters, candidates))
        thread.start()


