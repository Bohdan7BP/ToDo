#include <iostream>
#include "Task.h"
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using namespace std;

void setTask(Task& obj)
{
	char tempName[70];
	cout << "Enter task name" << endl;
	cin.getline(tempName, 70);
	cin.clear();
	int n = strlen(tempName);
	obj.taskName = new char[n + 1];
	strcpy_s(obj.taskName, static_cast<rsize_t>(n) + 1, tempName);
	cout << "Enter priority: 1 - low, 2 - middle, 3 - high, 4 - top " << endl;
	cin >> obj.priority;
	cin.ignore();
	char description[1000];
	cout << "Enter description" << endl;
	cin.getline(description, 1000);
	cin.clear();
	int m = strlen(description);
	obj.description = new char[m + 1];
	strcpy_s(obj.description, static_cast<rsize_t>(m) + 1, description);
	cout << "Enter task execution data dd.mm.yyyy: ";
	cin >> obj.execution.day >> obj.execution.month >> obj.execution.year;
	cout << "Enter task execution time hh:mm ";
	cin >> obj.execution.hour >> obj.execution.min;
	cout << "Enter task reminder time hh:mm ";
	cin >> obj.reminder.hour >> obj.reminder.min;
	cin.ignore();
}

void setTask(Task*& obj, int& size)
{
	Task* addTask = new Task[size + 1]; \
		for (int i = 0; i < size; i++)
		{
			addTask[i] = obj[i];
		}
	setTask(addTask[size]);
	//delete[] obj;

	obj = addTask;
	size++;
}

void getTask(Task& obj)
{
	cout << "-------------------------------------------------\n";
	(obj.execution.hour < 10) ? cout << "0" << obj.execution.hour : cout << obj.execution.hour;
	cout << ":";
	(obj.execution.min < 10) ? cout << "0" << obj.execution.min : cout << obj.execution.min;
	cout << "  " << obj.execution.day << "." << obj.execution.month << "." << obj.execution.year;
	cout << "  " << obj.taskName << "; priority ";
	switch (obj.priority)
	{
	case priority::low: cout << "low";
		break;
	case priority::middle: cout << "middle";
		break;
	case priority::high: cout << "high";
		break;
	case priority::top: cout << "top";
		break;
	}
	cout << endl;
	cout << "  " << obj.description << "; priority ";
	cout << endl;
	cout << "     Reminder time ";
	(obj.reminder.hour < 10) ? cout << "0" << obj.reminder.hour : cout << obj.reminder.hour;
	cout << ":";
	(obj.reminder.min < 10) ? cout << "0" << obj.reminder.min : cout << obj.reminder.min;
}

void getTask(Task*& obj, int& size)
{
	cout << "-------------------------TASK ORGANIZER------------------------------\n";
	for (int i = 0; i < size; i++)
	{
		getTask(obj[i]);
	}
}

void searcTaskByday(Task*& obj, int& size)
{
	int day, month, year;
	cout << "Enter task execution data dd.mm.yyyy: ";
	cin >> day >> month >> year;

	for (int i = 0; i < size; i++)
	{
		if (obj[i].execution.day == day && obj[i].execution.month == month && obj[i].execution.year == year)
		{
			getTask(obj[i]);
		}
	}
}

void searcTaskByMonth(Task*& obj, int& size)
{
	int  month, year;
	cout << "Enter task execution data mm.yyyy: ";
	cin >> month >> year;

	for (int i = 0; i < size; i++)
	{
		if (obj[i].execution.month == month && obj[i].execution.year == year)
		{
			getTask(obj[i]);
		}
	}
}

void searcTaskByWeek(Task*& obj, int& size)
{
	int day, month, year;
	cout << "Enter task execution data dd.mm.yyyy: ";
	cin >> day >> month >> year;

	for (int j = day; j < day + 7; j++)
	{
		for (int i = 0; i < size; i++)
		{
			if (obj[i].execution.day == j && obj[i].execution.month == month && obj[i].execution.year == year)
			{
				getTask(obj[i]);
			}
		}
	}
}

void writeToFile(Task* obj, int& size,const char* fileName)
{
	ofstream taskToFile;
	taskToFile.open(fileName, ios::out);
	if (!taskToFile.is_open())
	{
		cout << "ERROR";
		return;
	}
	taskToFile << size << endl;

	for (int i = 0; i < size; i++)
	{
		taskToFile << obj[i].execution.hour << '\t';
		taskToFile << obj[i].execution.min << '\t';
		taskToFile << obj[i].execution.day << '\t';
		taskToFile << obj[i].execution.month << '\t';
		taskToFile << obj[i].execution.year << '\t';

		int nameSize = strlen(obj[i].taskName);
		int descriptionSize = strlen(obj[i].description);
		
		taskToFile << nameSize << '\t';
		taskToFile << obj[i].taskName<< '\t';
		taskToFile << obj[i].priority<< '\t';
		taskToFile << descriptionSize << '\t';
		taskToFile << obj[i].description<< '\t';
		taskToFile << obj[i].reminder.hour<< '\t';
		taskToFile << obj[i].reminder.min<< '\t';
		if (i < size - 1) taskToFile << endl;
	}	
	taskToFile.close();
}

void readFromFile(Task* &obj, int& size, const char* fileName)
{
	ifstream taskFromFile;
	taskFromFile.open(fileName, ios::in);
	if (!taskFromFile.is_open())
	{
		cout << "ERROR";
		return;
	}
	int N = 0;
	taskFromFile >> N;
	Task* returnToWork = new Task[N];
	int i = 0;
	while(!taskFromFile.eof())
	{
		int nameSize = 0;
		int descriptionSize = 0;
		taskFromFile >> returnToWork[i].execution.hour;
		taskFromFile >> returnToWork[i].execution.min;
		taskFromFile >> returnToWork[i].execution.day;
		taskFromFile >> returnToWork[i].execution.month;
		taskFromFile >> returnToWork[i].execution.year;
		taskFromFile.ignore();
		taskFromFile.getline(obj[i].taskName, static_cast<std::streamsize>(nameSize) + 1);
		taskFromFile.clear();
		taskFromFile >> returnToWork[i].priority ;
		taskFromFile >> descriptionSize;

		taskFromFile.ignore();
		taskFromFile.getline(obj[i].description, static_cast<std::streamsize>(descriptionSize) + 1);
		taskFromFile.clear();
		taskFromFile >> returnToWork[i].reminder.hour;
		taskFromFile >> returnToWork[i].reminder.min ;
		i++;
	}
	
	taskFromFile.close();
	obj = returnToWork;
	size = N;
}