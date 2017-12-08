# A server application that receives messages from multi clients.

"""
admin admin is the teacher client
teacher decide attendance code
teacher add new student
teacher observe student situation
"""

from socket import *
import threading
import time


class Question:
    def __init__(self, question, answer):
        self.question = question
        self.answer = answer


class User:
    totalAttendantUser = 0
    attendance = False
    quizScore = 0
    bonus = 0.0
    timestamp = 999999999999

    def __init__(self, username, password):
        self.username = username
        self.password = password

    def toString(self):
        string = 'username: ' + self.username + '\nattendance: ' + str(self.attendance) + '\nquiz score: ' + str(self.quizScore) + '\nbonus: ' + str(self.bonus) + '\ntotal: ' + str(float(self.quizScore) + self.bonus) + '\ntimestamp: ' + str(self.timestamp) + '\n\n'
        return string

    # sort users according to timestamp
    def __lt__(self, other):
        return self.timestamp < other.timestamp

    def increaseAttendantUser(self):
        User.totalAttendantUser += 1


class ThreadedServer():
    # default attendanceCode
    attendanceCode = "0000"

    # default Users admin can add a new user
    users = [User('150120138', 'emre123'), User('150130101', '150130101'), User('1', '1'), User('2', '2')]

    # All questions and answers
    questions = [
        Question('_______ is the standard mechanism provided by TCP/IP for copying a file from one host to another.\nA)	TELNET\nB)	SMTP\nC)	TFTP\nD)	none of the above', 'D'),
        Question('FTP uses the services of ________.\nA)	UDP\nB)	IP\nC)	TCP\nD)	none of the above', 'C'),
        Question('In FTP, the well-known port ____ is used for the control connection and the well-known port ________ for the data connection.\nA)	21; 22\nB)	21; 20\nC)	20; 21\nD)	none of the above', 'B'),
        Question('In FTP, _______ is the service type used by the IP protocol because this is an interactive connection between a user (human) and a server.\nA)	maximize throughput\nB)	minimize delay\nC)	minimize error\nD)	none of the above', 'B'),
        Question('For control connection, FTP uses the __________ character set\nA)	regular ASCII\nB)	EBCDIC\nC)	NVT ASCII\nD)	none of the above', 'C'),
        Question('During an FTP session the control connection is opened _______.\nA)	exactly once\nB)	exactly twice\nC)	as many times as necessary\nD)	none of the above', 'A'),
        Question('During an FTP session the data connection is opened _______.\nA)	exactly once\nB)	exactly twice\nC)	as many times as necessary\nD)	none of the above', 'C'),
        Question('In FTP, a file can be organized into records, pages, or a stream of bytes. These are types of an attribute called _______.\nA)	file types\nB)	data structures\nC)	transmission modes\nD)	none of the above', 'B'),
        Question('In FTP, there are three types of _______: stream, block, and compressed.\nA)	file types\nB)	data structures\nC)	transmission modes\nD)	none of the above', 'C'),
        Question('	In FTP, ASCII, EBCDIC, and image define an attribute called _______.\nA)	file type\nB)	data structure\nC)	transmission mode\nD)	none of the above', 'A'),
    ]
    def listenToClient(self, client, addr):

        client.send("Enter the User ID and Password like '150120138 emre123': ")
        message = client.recv(1024)
        if message == "exit":
            print addr, " is closed"
            client.close()
            exit(0)
        # Only teacher know admin number and password (admin admin)
        # Teacher decide attendance code
        elif message == "admin admin":
            client.send("Enter the Attendance Code: ")
            message = client.recv(4)
            self.attendanceCode = message
            print addr, " Attendance Code: ", self.attendanceCode
            while True:
                client.send("Add new user (1)\n")
                client.send("Observe users (2)")
                message = client.recv(4)

                # add new user
                if message == '1':
                    client.send("Enter the User ID and Password like '150120138 emre123' for add new user:" )
                    message = client.recv(1024)
                    message = message.split()
                    username = message[0]
                    password = message[1]
                    user = User(username, password)
                    self.users.append(user)
                    client.send("New user added succesfully")

                # show user scores
                elif message == '2':
                    for user in self.users:
                        client.send(user.toString())

                # exit the system
                elif message == "exit":
                    print addr, " is closed"
                    client.close()
                    exit(0)

        # user section
        else:
            message = message.split()
            username = message[0]
            password = message[1]
            user = User(username, password)
            currentUser = self.checkUser(self.users, user)
            if currentUser:
                # each user attend quiz only one time
                if currentUser.attendance:
                    print addr, " is closed because of he/she want to attend more than one"
                    client.close()
                    exit(0)

                # attendance code decided by teacher
                client.send("Enter the Attendance Code: ")
                message = client.recv(4)

                if self.attendanceCode == message:
                    currentUser.attendance = True
                    print "User", username, " attend the class"
                    index = 1

                    # print questions
                    for question in self.questions:
                        questionNo = "\nQuestion " + str(index) + ": "
                        client.send(questionNo + question.question)
                        message = client.recv(1)
                        index += 1

                        # correnct answer
                        if message == question.answer or message == question.answer.lower():
                            print addr, "User", username, "select the correct answer for Question", (index-1)
                            currentUser.quizScore += 10

                    # timestamp
                    ts = time.time()
                    currentUser.timestamp = ts
                    print addr, " is closed"

                    # increase static attendant user number
                    currentUser.increaseAttendantUser()

                    # sort according to timestamp
                    self.users.sort()
                    index = 0
                    for user in self.users:
                        # bonus share only attandant users
                        user.bonus = float(100 - (index * float(100 / user.totalAttendantUser)))
                        index += 1
                        if index == user.totalAttendantUser:
                            break
                    client.close()
                    exit(0)



    def checkUser(self, usersDB, userCurrent):
        for userDB in usersDB:
            if userDB.username == userCurrent.username and userDB.password == userCurrent.password:
                return userDB

        return False


    def __init__(self, serverPort):
        try:
            serverSocket = socket(AF_INET, SOCK_STREAM)

        except:

            print "Socket cannot be created!!!"
            exit(1)

        print "Socket is created..."

        try:
            serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        except:

            print "Socket cannot be used!!!"
            exit(1)

        print "Socket is being used..."

        try:
            serverSocket.bind(('', serverPort))
        except:

            print "Binding cannot de done!!!"
            exit(1)

        print "Binding is done..."

        try:
            serverSocket.listen(45)
        except:

            print "Server cannot listen!!!"
            exit(1)

        print "The server is ready to receive"

        while True:
            connectionSocket, addr = serverSocket.accept()

            threading.Thread(target=self.listenToClient, args=(connectionSocket, addr)).start()


if __name__ == "__main__":
    serverPort = 12000
    ThreadedServer(serverPort)
