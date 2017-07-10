#pragma once
#include "Student.h"
#include <string.h>

using namespace std;
const int MAX_STRING_LENGTH = 128;
const int BASIC_GROUP_SIZE = 20;

class AcademyGroup
{
private:
	Student** group;
	int size;
	int count;

	void expand_group();
public:

	AcademyGroup();
	~AcademyGroup();
	void add_student(Student* StPtr);	
	void delete_student(int i);
	void edit_student(int i, Student* StPtr) const;
	void sort(int sort_type);
	
	const int get_count() const 
	{
		return count; 
	}
	const Student& get_student(int indx) const 
	{ 
		return *group[indx]; 
	}

	/*enum sort_type
	{
		no_sort = 0,
		by_name = 1,
		by_surname = 2,
		by_average_score = 3
	};*/
};