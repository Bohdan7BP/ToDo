#include <iostream>
#include "Task.h"

int main()
{
    int N = 0;
    Task *list;
    //setTask(list, N);
    //setTask(list, N);
    //setTask(list, N);
  
    readFromFile(list, N, "ToDo.txt");
   
    getTask(list, N);

   // getTask(list, N);
}