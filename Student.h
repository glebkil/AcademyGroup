#pragma once
#define PHONE_LENGTH 14

class Student
{
private:
	char * name;
	char * surname;
	int age;
	char phone[PHONE_LENGTH];
	double average;

public:
	Student();
	Student(const char * name, const char * surname, int age, const char * phone, double average);
	~Student();
	Student (const Student &obj);

	char* get_name() const { return name; }
	char * get_surname() const { return surname; }
	int get_age() const { return age; }
	double get_average() const { return average; }
	const char * get_phone() const {return phone;}

	void set_name(const char * name);
	void set_surname(const char * surname);
	void set_phone(const char * phone);
	void set_age(int age) { this->age = age;  }
	void set_average(double average) { this->average = average;  }
};
