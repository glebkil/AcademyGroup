/*�������� ���������, ����������� ����������� 
������ ��������� ������������� ������. ��������� 
��������� ������ �������������
������������ ��������� �����������:
a. ���������� ��������� � ������;
b. �������� �������� �� ������;
c. ����������� ������ ��������;
d. ������ ������������� ������;
e. ���������� ������ ���������;
f. ����� �������� �� ��������� ��������;
g. ���������� ������ ��������� � ���� (��� ���������� ������ ���������);
h. �������� ������ ��������� �� ����� (��� ������ ���������);
i. ����� �� ���������.
��� ���������� ��������� �������
������������ ��������� ������������ ������ ��� �������� ������ ��������� 
(���������� ������������ ������ ���������� �� ������� ������ Student).*/

#include "Student.h"
#include "AcademyGroup.h"
#include "Console.h"
#include "DataBase.h"

#include <iostream>
using namespace std;

//C:\Users\Gleb\Documents\Visual Studio 2017\Projects\AcedemyGroup\AcedemyGroup

int main()
{
	DataBase DB;
	AcademyGroup SNU_1621;

	DB.deserialize(SNU_1621);
	Console::run_app(SNU_1621);
	DB.serialize(SNU_1621);
	exit(0);
}

/*ToDo
overload assignment operator for Student 

overload  operator () for Student to set values easily 

overload << for student and acedemy group

convert phone to standart string with 128 characters 

check choosing_student func

check console class. is it ok that all func take DM?

What is assert? 
*/