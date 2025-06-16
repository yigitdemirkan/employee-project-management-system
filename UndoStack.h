#include <iostream>
#include <string>
using namespace std;

#ifndef HW3_UNDOSTACK_H
#define HW3_UNDOSTACK_H

struct StackNode
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;
    StackNode(const char & o, const string & e, const string & p, const int & pp, StackNode * n)
            : operation(o), employee_name(e),project_name(p),project_priority(pp), next(n)
    {}
};

class UndoStack {
public:
    UndoStack();
    void push(char operation, string employee_name, string project_name, int priority);
    void pop(char & operation, string & employee_name, string & project_name, int & priority);
    bool isEmpty();
    void clear();

private:
    StackNode * top;
};


#endif //HW3_UNDOSTACK_H
