#pragma once
struct DataTask
{
	int min;
	int hour;
	int day;
	int month;
	int year;
};
enum priority
{
	low = 1, middle, high, top
};
struct Task
{
	DataTask execution;
	char* taskName;
	int priority;
	char* description;
	DataTask reminder;
};

void setTask(Task& obj);
void setTask(Task*& obj, int& size);
void getTask(Task& obj);
void getTask(Task*& obj, int& size);
void searcTaskByday(Task*& obj, int& size);
void searcTaskByMonth(Task*& obj, int& size);
void searcTaskByWeek(Task*& obj, int& size);
void writeToFile(Task* obj, int& size, const char* fileName);
void readFromFile(Task* &obj, int& size, const char* fileName);