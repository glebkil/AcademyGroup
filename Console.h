#pragma once
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "AcademyGroup.h"

class Console
{
	private:
		static void menu( AcademyGroup& DM);
		static void menu_or_exit( AcademyGroup& DM);

		static int choosing_student(AcademyGroup& DM);
		static void adding_student(AcademyGroup& DM);
		static void print_student(const Student* st_ptr ) ;
		static void printing_students(AcademyGroup& DM);
		static void sorting_students(AcademyGroup& DM);
		static void editing_student(AcademyGroup& DM);
		static void searching_student(AcademyGroup& DM);
		static void deleting_student( AcademyGroup& DM);
	public:
		static void run_app( AcademyGroup& DM); //Academic group occures to be a Data Model
};
