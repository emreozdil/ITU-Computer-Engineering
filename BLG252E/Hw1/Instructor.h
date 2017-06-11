/*
* @Author
* Student Name: Emre Özdil
* Student ID : 150120138
* Date: 26/03/2016
*/

#pragma once
#include <string>
using namespace std;
class Instructor
{
public:
	// Constructor Destructor
	Instructor();
	Instructor(const string&, const string&);
	Instructor(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&);
	~Instructor();

	// Getter Methods
	string getTitle() const { return Title; };
	string getFirstName() const { return FirstName; };
	string getLastName() const { return LastName; };
	string getPhoneNumber() const { return PhoneNumber; };
	string getRoomNumber() const { return RoomNumber; };
	string getUserName() const { return UserName; };
	string getEmailAddress() const { return EmailAddress; };
	string getCourses() const { return Courses; };

	// Setter Methods
	void setTitle(string Title) { this->Title = Title; };
	void setFirstName(string FirstName) { this->FirstName = FirstName; };
	void setLastName(string LastName) { this->LastName = LastName; };
	void setPhoneNumber(string PhoneNumber) { this->PhoneNumber = PhoneNumber; };
	void setRoomNumber(string RoomNumber) { this->RoomNumber = RoomNumber; };
	void setUserName(string UserName) { this->UserName = UserName; };
	void setEmailAddress(string EmailAddress) { this->EmailAddress = EmailAddress; };
	void setCourses(string Courses) { this->Courses = Courses; };

	//Function
	void Print() const;

private:
	string Title;
	string FirstName;
	string LastName;
	string PhoneNumber;
	string RoomNumber;
	string UserName;
	string EmailAddress;
	string Courses;
};

// Constructor
Instructor::Instructor()
{
}
Instructor::Instructor(const string& FirstName, const string& LastName)
{
	setFirstName(FirstName);
	setLastName(LastName);
}
Instructor::Instructor(const string& Title, const string& FirstName, const string& LastName, const string& PhoneNumber, const string& RoomNumber, const string& UserName, const string& EmailAddress, const string&Courses)
{
	setTitle(Title);
	setFirstName(FirstName);
	setLastName(LastName);
	setPhoneNumber(PhoneNumber);
	setRoomNumber(RoomNumber);
	setUserName(UserName);
	setEmailAddress(EmailAddress);
	setCourses(Courses);
}
// Destructor
Instructor::~Instructor()
{
}

inline void Instructor::Print() const
{
	cout << "Title: " << Title << endl;
	cout << "First Name: " << FirstName << endl;
	cout << "SurName: " << LastName << endl;
	cout << "Telephone Number: " << PhoneNumber << endl;
	cout << "Room Number: " << RoomNumber << endl;
	cout << "User Name: " << UserName << endl;
	cout << "Email: " << EmailAddress << endl;
	cout << "Courses: [" << Courses << "]" << endl;
	cout << "--------------------------------" << endl;
}

// Operator Overloading
bool operator==(Instructor& firstInstructor, Instructor& secondInstructor)
{
	if (firstInstructor.getTitle() == secondInstructor.getTitle() &&
		firstInstructor.getFirstName() == secondInstructor.getFirstName() &&
		firstInstructor.getLastName() == secondInstructor.getLastName() &&
		firstInstructor.getPhoneNumber() == secondInstructor.getPhoneNumber() &&
		firstInstructor.getRoomNumber() == secondInstructor.getRoomNumber() &&
		firstInstructor.getUserName() == secondInstructor.getUserName() &&
		firstInstructor.getCourses() == secondInstructor.getCourses())
	{
		return true;
	}
	else return false;
}
