from socket import *
import os

def cls():
    os.system('cls' if os.name=='nt' else 'clear')

serverName="192.168.2.179"
serverPort=12000

clientSocket=socket(AF_INET,SOCK_STREAM)

clientSocket.connect((serverName,serverPort))

message=clientSocket.recv(1024) # for welcome and authentication info
print message

while True:

	try:
		answer=raw_input('Type message:')

		if message[1:9]=="Question":
			answer2=raw_input("Save an answer? (Y/N):")

			if answer2[0]=='Y' or answer2[0]=='y':
				clientSocket.send(answer)
			else:
				print "Ok, give your new answer!\n"
				continue
		elif answer=="exit":
			clientSocket.close()
			exit(0)
		else:
			clientSocket.send(answer)
		cls() # to clear terminal
		message=clientSocket.recv(1024)

		print message

	except:
		clientSocket.close()
		exit(0)
