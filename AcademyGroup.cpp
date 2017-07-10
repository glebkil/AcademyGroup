#include "AcademyGroup.h"


template<class T>
void swap( T& arg1,  T& arg2)
{
	T temp = arg2;
	arg2 = arg1;
	arg1 = temp;
}

bool compare_strings(const char * str1, const char* str2)
{
	int min_len = strlen(str1) <= strlen(str2) ? strlen(str1) : strlen(str2);
	for (int i = 0; i < min_len; i++)
	{
		if (str1[i] != str2[i])
		{
			if (str1[i] - str2[i] > 0)
			{
				return false;
			}
			else 
			{
				return true;
			}
		}
	}
	return true;
}

bool compare_names( const Student* st1, const Student* st2)
{
	return compare_strings(st1->get_name(), st2->get_name());
}

bool compare_surnames(const Student* st1, const Student* st2)
{
	return compare_strings(st1->get_surname(), st2->get_surname());
}

bool compare_averages(const Student* st1, const  Student* st2)
{
	if (st1->get_average() - st2->get_average() >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}

	//return st1->getAverage() - st2->getAverage() > 0;
}

void bsort(Student** group, int el_num, bool(*comparator)(const Student* st1, const Student* st2))
{
	for (int j = el_num-1; j >= 0; j--)
	{
		for (int i = 0; i < j; i++)
		{
			if (!comparator(group[i], group[i + 1]))
			{
				swap(group[i], group[i + 1]);
			}
		}
	}
	
}

void AcademyGroup::sort(int sort_type)
{
	switch (sort_type)
	{
		case 1:
		bsort(group, get_count(), compare_names);
		break;
		case 2:
		bsort(group, get_count(), compare_surnames);
		break;
		case 3:
		bsort(group, get_count(), compare_averages);
		break;
	}
}

AcademyGroup::AcademyGroup()
{
	group = new Student* [BASIC_GROUP_SIZE];
	count = 0;
	size = BASIC_GROUP_SIZE;
}

AcademyGroup::~AcademyGroup()
{
	for (int i = 0; i < count; i++)
	{
		delete group[i];
	}
	delete[] group;
}

void AcademyGroup::add_student(Student * StPtr)
{
	if (count == size)
	{
		expand_group();
		group[count] = StPtr;
		count++;
	}
	else
	{
		group[count] = StPtr;
		count++;
	}
}

void AcademyGroup::delete_student(int i)
{
	if (i == -1)
	{
		return;
	}
	delete group[i];
	for (; i < count-1; i++)
	{
		group[i] = group[i + 1];
	}
	count--;
}

void AcademyGroup::edit_student(int i, Student * StPtr) const
{
	group[i] = StPtr;
}

void AcademyGroup::expand_group()
{
	Student ** temp_ptr = new Student*[size + BASIC_GROUP_SIZE];
	for (int i = 0; i < count; i++)
	{
		temp_ptr[i] = group[i];
	}
	delete[] group;
	group = temp_ptr;
	size += BASIC_GROUP_SIZE;
}

