#include "UndoStack.h"

UndoStack:: UndoStack(){
    top = nullptr;
}
void UndoStack::  push(char operation, string employee_name, string project_name, int priority){
    StackNode *newNode;
    if(isEmpty())
    {
        newNode = new StackNode(operation, employee_name, project_name,priority, nullptr);
        top = newNode;
    }
    else
    {
        newNode = new StackNode(operation, employee_name, project_name,priority, top);
        top = newNode;
    }
}

void UndoStack::  pop(char & operation, string & employee_name, string & project_name, int & priority){
    StackNode *temp;

    if(isEmpty())
    {
        cout<<"Stack is empty!";
    }

    else
    {
        operation = top->operation;
        employee_name = top -> employee_name;
        project_name = top -> project_name;
        priority = top -> project_priority;
        temp = top->next;
        delete top;
        top = temp;
    }
}

bool UndoStack:: isEmpty(){
    if(top == nullptr){
        return true;
    }
    return false;
}

void UndoStack::  clear(){
    char operation = ' ';
    string employee_name = "";
    string project_name = "";
    int priority = -1;
    while(!isEmpty()){
        pop(operation, employee_name, project_name, priority);
    }
}