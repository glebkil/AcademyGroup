#pragma once
#include <iostream>
#include "AcademyGroup.h"

class DataBase
{
private:
	FILE * DB;

	bool Open(const char* mode);
	void Close();
public:
	DataBase() { DB = nullptr; }
	//~DataBase() { fclose(DB); }

	void serialize(const AcademyGroup& DM);
	void deserialize(AcademyGroup& DM);
};