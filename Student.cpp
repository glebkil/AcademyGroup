#include "Student.h"
#include <string.h>
#include <ctype.h>

void CopyStr(char*& field, const char* str)
{
	if (field)
	{
		delete[] field;
	}	
	auto len = strlen(str);
	field = new char[len + 1];
	strcpy_s(field, len + 1, str);
}

Student::Student() : name(NULL), surname(NULL), age(0), average(0)
{
	phone[0] = 0;
}

Student::Student(const char * name, const char * surname, int age, const char * phone, double average)
	: name(NULL), surname(NULL), age(age), average(average)
{ 
	CopyStr(this->name, name);
	CopyStr(this->surname, surname);

	strcpy_s(this->phone, PHONE_LENGTH, phone);
}

Student::~Student()
{
	delete[] name;
	delete[] surname;
}

Student::Student(const Student & obj) : name(NULL), surname(NULL)
{
	CopyStr(name, obj.name);
	CopyStr(surname, obj.surname);

	strcpy_s(phone, PHONE_LENGTH, obj.phone);
	age = obj.age;
	average = obj.average;
}

void Student::set_name(const char * name)
{
	CopyStr(this->name,name);
	this->name[0] = toupper(this->name[0]);
}

void Student::set_surname(const char * surname)
{
	CopyStr(this->surname, surname);
	this->surname[0] = toupper(this->surname[0]);
}

void Student::set_phone(const char * phone)
{
	strcpy_s(this->phone, PHONE_LENGTH, phone);
}
 
