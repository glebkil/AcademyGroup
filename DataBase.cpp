#include <Windows.h>
#include <iostream>
#include <sstream>
#include "DataBase.h"
#pragma once

#define WAY_TO_A_FILE "DBFile.txt"

bool DataBase::Open(const char* mode)
{
	errno_t res = fopen_s(&DB, WAY_TO_A_FILE, mode);
	if (res != 0)
	{
		cout << "Error in opening file DB.txt" << endl;
		return false;
	}
	return true;
}

void DataBase::Close()
{
	if (DB == NULL)
		return;
	fclose(DB);
	DB = NULL;
}

void OutputDebug(const char* szFormat, ...)
{
	char szBuff[1024];
	va_list arg;
	va_start(arg, szFormat);
	_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
	va_end(arg);

	OutputDebugString(szBuff);
}

void fwrite_safe(const void *buf, size_t size, size_t count, FILE* file)
{
	int cnt = fwrite(buf, size, count, file);
	if (cnt != count)
		throw "error write buffer";
	OutputDebug("block size=%d, pos=%d\r\n", size*count, ftell(file));
}

void fread_safe(void *buf, size_t size, size_t count, FILE* file)
{
	int cnt = fread(buf, size, count, file);
	if (cnt != count)
		throw "error read buffer";
	OutputDebug("block size=%d, pos=%d\r\n", size*count, ftell(file));
}

void WriteString(FILE* file, const char* str)
{
	int strLen = strlen(str);
	fwrite_safe(&strLen, sizeof(int), 1, file);
	fwrite_safe(str, strLen + 1, 1, file);
}

template<class T>
void Write(FILE* file, const T value)
{
	fwrite_safe(&value, sizeof(T), 1, file);
}

typedef void (Student::*SetStringHandler)(const char* str);
void ReadString(FILE* file, Student& student, SetStringHandler setter)
{
	int len;
	fread_safe(&len, sizeof(len), 1, file);
	char* str = new char[len + 1];
	fread_safe(str, len + 1, 1, file);
	(student.*setter)(str);
	delete[] str;
}

int ReadInt(FILE* file)
{
	int value;
	fread_safe(&value, sizeof(int), 1, file);
	return value;
}

double ReadDouble(FILE* file)
{
	double value;
	fread_safe(&value, sizeof(double), 1, file);
	return value;
}

void DataBase::serialize(const AcademyGroup & DM)
{
	if (!Open("w+"))
		throw "error append into file";

	int St_count = DM.get_count();
	fwrite_safe(&St_count, sizeof(St_count), 1, DB);

	for (int i = 0; i < St_count; i++)
	{
		auto& student = DM.get_student(i);

		WriteString(DB, student.get_name());

		WriteString(DB, student.get_surname());

		fwrite_safe(DM.get_student(i).get_phone(), PHONE_LENGTH, 1, DB);

		Write(DB, student.get_age());

		Write(DB, student.get_average());
	}
	Close();
}

void DataBase::deserialize(AcademyGroup& DM)
{
	if (!Open("r"))
		return;

	int student_num = ReadInt(DB);

	for (int i = 0; i < student_num; i++)
	{
		Student* stPtr = new Student();

		ReadString(DB, *stPtr, &Student::set_name);

		ReadString(DB, *stPtr, &Student::set_surname);

		char temp_phone[PHONE_LENGTH];
		fread_safe(temp_phone, PHONE_LENGTH, 1, DB);
		stPtr->set_phone(temp_phone);

		stPtr->set_age(ReadInt(DB));

		stPtr->set_average(ReadDouble(DB));

		DM.add_student(stPtr);
	}
	
	Close();
}
