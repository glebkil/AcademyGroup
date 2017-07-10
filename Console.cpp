#include "Console.h"
#include "AcademyGroup.h"
#include <ctype.h>

#define MENU_ITEM_CALL(function_to_call)	\
system("cls");								\
function_to_call;							\
Console::menu_or_exit(DM);

void chars_toupper(char * source_string) // changes the passed string
{
	char *temp_ptr = source_string;
	while (*temp_ptr)
	{
		*temp_ptr = toupper(*temp_ptr);
		temp_ptr++;
	}
}

void flush_stdin()
{
	cin.clear();
	while (cin.get() != '\n');
}

double input_number()
{
	char str[MAX_STRING_LENGTH];
	//gets_s(str, MAX_STRING_LENGTH - 1);
	cin >> str;
	double result = atof(str);
	if (result == NULL)
	{
		cout << "Incorrect input." << endl;
		input_number();
	}
	else
	{
		return result;
	}
}

double input_positive_number()
{
	double result = input_number();
	if (result <= 0)
	{
		cout << "Incorrect input. Number should be biger than 0" << endl;
		input_positive_number();
	}

	else
	{
		return result;
	}
}

char* input_phone()
{
	char* temp_phone = new char[MAX_STRING_LENGTH];
	cin >> temp_phone;
	if (strlen(temp_phone) >= PHONE_LENGTH)
	{
		cout << "Incorrect input" << endl;
		input_phone();
	}

	temp_phone[PHONE_LENGTH - 1] = 0;
	return temp_phone;
}

char* read_string()
{
	char* temp_str = new char[MAX_STRING_LENGTH + 1];
	cin >> temp_str;
	return temp_str;
}

void Console::menu(AcademyGroup& DM)
{
	system("cls");

	cout << "1. Add a student" << endl;
	cout << "2. Delete a student" << endl;
	cout << "3. Edit a student" << endl;
	cout << "4. See all students" << endl;
	cout << "5. Sort" << endl;
	cout << "6. Search" << endl;
	cout << "7. Exit" << endl;

	switch ((int)input_number())
	{
	case 1:
		MENU_ITEM_CALL(adding_student(DM))
			break;
	case 2:
		MENU_ITEM_CALL(deleting_student(DM))
			break;
	case 3:
		MENU_ITEM_CALL(editing_student(DM))
			break;
	case 4:
		MENU_ITEM_CALL(printing_students(DM))
			break;
	case 5:
		MENU_ITEM_CALL(sorting_students(DM))
			break;
	case 6:
		MENU_ITEM_CALL(searching_student(DM))
			break;
	case 7:
		return;
		break;
	default:
		menu(DM);
		break;
	}
}

void Console::menu_or_exit( AcademyGroup& DM)
{
	cout << endl;

	cout << "Enter 1 to go to main menu" << endl;
	cout << "Enter 2 to exit" << endl;

	switch ((int)input_number())
	{
	case 1:
		menu(DM);
		break;
	case 2:
		return;
		break;
	default:
		menu_or_exit(DM);
		break;
	}
}

int Console::choosing_student(AcademyGroup& DM)
{
	if (DM.get_count() == 0)
	{
		cout << "No students yet";
		menu_or_exit(DM);
	}

	printing_students(DM);

	cout << endl << "Input number of student:  ";
	int chosen_student = (int)input_positive_number();
	chosen_student--;

	if (chosen_student < 0 || chosen_student > DM.get_count())
	{
		cout << "No student with that number" << endl;
		menu_or_exit(DM);
	}

	return chosen_student;
}

void input_student_data(Student* stPtr)
{
	cout << "Input name: ";
	stPtr->set_name(read_string());

	cout << "Input surname: ";
	stPtr->set_surname(read_string());

	cout << "Input phone: ";
	stPtr->set_phone(input_phone());

	flush_stdin();

	cout << "Input age: ";
	stPtr->set_age((int)input_positive_number());

	cout << "Input average: ";
	stPtr->set_average(input_positive_number());
}

void Console::adding_student(AcademyGroup& DM)
{
	Student* stPtr = new Student();

	cout << "You are adding a student" << endl;

	input_student_data(stPtr);

	DM.add_student(stPtr);
}

void Console::print_student(const Student* st_ptr)
{
	cout << st_ptr->get_name() << " " << st_ptr->get_surname() << endl;
	cout << "Phone: " << st_ptr->get_phone() << " Age: " << st_ptr->get_age()
		<< " Average: " << st_ptr->get_average() << endl << endl;
}

void Console::printing_students(AcademyGroup & DM)
{
	if (DM.get_count() == 0)
	{
		cout << "No students in the group yet" << endl;
	}

	for (int i = 0; i < DM.get_count(); i++)
	{
		cout << "Student " << i + 1 << ":" << endl;
		print_student(&DM.get_student(i));
	}
}

void Console::sorting_students(AcademyGroup & DM)
{
	cout << "How do you want to sort a group?" << endl;
	cout << "1. Sort by name" << endl;
	cout << "2. Sort by surname" << endl;
	cout << "3. Sort by average" << endl;

	switch ((int)input_number())
	{
	case 1:
		DM.sort(1);
		break;
	case 2:
		DM.sort(2);
		break;
	case 3:
		DM.sort(3);
		break;
	default:
		cout << "No such option" << endl;
		menu_or_exit(DM);
		break;
	}
	cout << "Here we are: " << endl;
	printing_students(DM);
}

void Console::editing_student(AcademyGroup& DM)
{
	int chosen_student = choosing_student(DM);

	Student* stPtr = new Student();

	input_student_data(stPtr);

	DM.edit_student(chosen_student, stPtr);
}

void Console::deleting_student( AcademyGroup& DM)
{
	DM.delete_student(choosing_student(DM));
	cout << "Delete successful" << endl;
}

 void Console::run_app( AcademyGroup& DM)
{
	menu(DM);
}

 void Console::searching_student(AcademyGroup & DM)
 {
	 int count = 0; 
	 cout << "Enter name, sername or phone number to look for:";
	 char* key = new char[MAX_STRING_LENGTH];
	 cin >> key;
	 chars_toupper(key);

	 for (int i = 0; i < DM.get_count(); i++)
	 {
		 Student temp_st = DM.get_student(i);
		 chars_toupper(temp_st.get_name());
		 chars_toupper(temp_st.get_surname());

		 if (strstr(temp_st.get_name(), key) || strstr(temp_st.get_surname(), key) || strstr(temp_st.get_phone(), key))
		 {
			 print_student(&DM.get_student(i));
			 count++;
		 }
	 }

	 if (count == 0)
	 {
		 cout << "Nothing found" << endl;
	 }
 }

 