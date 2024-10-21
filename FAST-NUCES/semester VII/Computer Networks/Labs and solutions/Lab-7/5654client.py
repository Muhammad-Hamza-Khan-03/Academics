import socket
import os

def load_voted():
    voted = set()
    if os.path.exists("output.txt"):
        with open("output.txt", "r") as f:
            for line in f:
                name, cnic, vote= line.strip().split(',')
                voted.add(cnic)
    return voted

def main():
    host = '127.0.0.1'
    port = 12345

    voted = load_voted()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))

        while True:
            name = input("Enter your name: ")
            cnic = input("Enter your CNIC number: ")

            if cnic in voted:
                print("You have already voted. You cannot vote again.")
                continue
            
            f = open("candidates_list.txt", "r")
            for line in f:
            	print(line)
            
            polling = input("Enter your voting symbol: ")
            message = f"{name},{cnic},{polling}"
            s.sendall(message.encode('utf-8'))
            
            # Receive the response from the server
            data = s.recv(1024).decode('utf-8')
            print(f"Server response: {data}")
            
            if "successfully" in data:
                with open("output.txt", "a") as f:
                    f.write(f"{name},{cnic},{polling}\n")
                voted.add(cnic)
            
            # Ask if the user wants to continue
            ans = input('\nnext Candidate(y/n): ')
            if ans.lower() != 'y':
                break

if __name__ == '__main__':
    main()
