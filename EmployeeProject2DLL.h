#include <iostream>
#include <string>
using namespace std;

#ifndef HW3_EMPLOYEEPROJECT2DLL_H
#define HW3_EMPLOYEEPROJECT2DLL_H

struct ProjectNode
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;
    ProjectNode(const string & pn, const int & pp, ProjectNode * n, ProjectNode * p)
            : project_name(pn), project_priority(pp), next(n), prev(p)
    {}
};

struct EmployeeNode
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;
    EmployeeNode(const string & en, ProjectNode * h, ProjectNode * t, EmployeeNode * d)
            : employee_name(en), head(h), tail(t), down(d)
    {}
};


class EmployeeProject2DLL {
public:
    EmployeeProject2DLL();
    bool isEmployeeAssignedToProject(string employee_name, string project_name);
    bool updateProjectPriority(string employee_name, string project_name, int & priority);
    bool assignEmployeeToProject(string employee_name, string project_name, int priority);
    void withdrawEmployeeFromProject(string employee_name, string project_name, int & priority);
    void printTheEntireList();
    void printEmployeeProjects(string employee_name, int order);
    void undo(char operation_type, string employee_name, string project_name, int priority);
    void clear();

private:
    ProjectNode * next;
    ProjectNode * prev;
    ProjectNode * tail;
    EmployeeNode * down;
    ProjectNode * head;
    EmployeeNode * head_2dll;
    bool checkPriority (string employee_name, string project_name, int & priority);
    EmployeeNode * isInEmployeeList (string employee_name);
};


#endif //HW3_EMPLOYEEPROJECT2DLL_H
