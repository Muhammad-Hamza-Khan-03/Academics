File = file.txt
all:pipe sender reciever rem_pipe

pipe: pipe.c
	gcc -o pipe pipe.c

sender: sender.c
				gcc -o sender sender.c

reciever: reciever.c
			gcc -o reciever reciever.c

rem_pipe: rem_pipe.c
			gcc -o rem_pipe rem_pipe.c

run: all
	./pipe
	./sender $(File)
	./reciever
	./rem_pipe