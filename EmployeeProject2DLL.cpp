//Yigit Demirkan

#include "EmployeeProject2DLL.h"

//This default constructor initializes the private variables.
EmployeeProject2DLL :: EmployeeProject2DLL(){
    next = nullptr;
    prev = nullptr;
    head_2dll = nullptr;
    tail = nullptr;
    down = nullptr;
    head = nullptr;
}

//This function checks whether the employee is assigned to given project or not.
bool EmployeeProject2DLL :: isEmployeeAssignedToProject(string employee_name, string project_name){
    EmployeeNode * ptr = head_2dll;
    while (ptr != nullptr){
        if (employee_name == ptr -> employee_name){
            ProjectNode * ptr_p = ptr -> head;
            while (ptr_p != nullptr){
                if (project_name == ptr_p -> project_name){
                    return true;
                }
                else{
                    ptr_p = ptr_p -> next;
                }
            }
        }
        ptr = ptr -> down;
    }
    return false;
}

/*
This private function checks two things:
- Is the new given priority for an existing project same with previous one?
- Is the given project-priority pair is already exist?
If the above two cases hold, it returns false. Otherwise, it returns false.
*/
bool EmployeeProject2DLL :: checkPriority(string employee_name, string project_name, int & priority){
    EmployeeNode * ptr = head_2dll;
    while (ptr != nullptr){
        if (employee_name == ptr -> employee_name){
            ProjectNode*ptr_p = ptr -> head;
            while (ptr_p != nullptr){
                if (priority == ptr_p -> project_priority) {
                    if (project_name == ptr_p -> project_name) {
                        cout << "The project priority is already the same as the new priority." << endl;
                        return false;
                    }
                    else{
                        cout << "The project priority has not been updated because there is another project with the same priority." << endl;
                        return false;
                    }
                }
                else{
                    ptr_p = ptr_p -> next;
                }
            }
        }
        ptr = ptr -> down;

    }
    return true;
}

/*
This function updates the priority of an existing project and orders the projects of an employee accordingly.
*/
bool EmployeeProject2DLL ::updateProjectPriority(string employee_name, string project_name, int & priority){
    if (!checkPriority(employee_name, project_name, priority)){ //Checking the availability for update.
        return false;
    }
    else{
        EmployeeNode * ptr = head_2dll;
        while (ptr != nullptr) {
            if (employee_name == ptr->employee_name) {
                ProjectNode *ptr_p = ptr->head;
                while (ptr_p != nullptr) {
                    if (project_name == ptr_p -> project_name){
                        int temp = ptr_p -> project_priority;
                        ptr_p -> project_priority = priority;
                        priority = temp; //changing the priority
                        if (ptr_p -> prev != nullptr){ //If the node which will be updated is not at the beginning
                            if (ptr_p -> project_priority < ptr_p -> prev -> project_priority){ //Checking the left of the list for correct placement of updated node.
                                ProjectNode*iteration = ptr_p;
                                while (iteration -> prev != nullptr && (ptr_p -> project_priority < iteration -> prev -> project_priority) ){
                                    iteration = iteration->prev;
                                }
                                if (iteration -> prev == nullptr){ //The correct place for updated node is head.
                                    ProjectNode * add = new ProjectNode(ptr_p->project_name, ptr_p-> project_priority, iteration, nullptr);
                                    ptr-> head = add;
                                    iteration -> prev = add;
                                    if (ptr_p -> next == nullptr){ //If the changed node is at the end of the list initially
                                        ptr -> tail = ptr_p -> prev;
                                        ptr_p -> prev -> next = nullptr;
                                        delete ptr_p; //After transferring the information, the old node is deleted.
                                        ptr_p = nullptr;
                                        ptr = nullptr;
                                    }
                                    else{//The correct place for updated node is any other place but head.
                                        ptr_p -> prev -> next = ptr_p -> next;
                                        ptr_p -> next -> prev = ptr_p -> prev;
                                        delete ptr_p;
                                        ptr_p = nullptr;
                                        ptr = nullptr;
                                    }
                                }
                            }
                            else{ //No change in place is needed
                                ptr_p = nullptr;
                                ptr = nullptr;
                            }
                        }
                        else if (ptr_p -> next != nullptr){ //If the node which will be updated is not at the end
                                if (ptr_p -> project_priority > ptr_p -> next -> project_priority){ //Checking the right of the list for correct placement of updated node.
                                  ProjectNode*iteration = ptr_p;
                                  while (iteration -> next != nullptr && (ptr_p -> project_priority > iteration -> next -> project_priority) ){
                                      iteration = iteration->next;
                                  }
                                  if (iteration -> next == nullptr){ //The correct place for updated node is tail.
                                      ProjectNode * add = new ProjectNode(ptr_p->project_name, ptr_p-> project_priority, nullptr, iteration);
                                      ptr -> tail = add;
                                      iteration -> next = add;
                                      if (ptr_p -> prev == nullptr){ //If the changed node is at the beginning of the list initially
                                          ptr -> head = ptr_p -> next;
                                          ptr_p -> next -> prev = nullptr;
                                      }
                                      delete ptr_p; //After transferring the information, the old node is deleted.
                                      ptr_p = nullptr;
                                      ptr = nullptr;
                                  }
                                  else{ //The correct place for updated node is any other place but tail.
                                      ProjectNode * add = new ProjectNode(ptr_p->project_name, ptr_p-> project_priority, iteration-> next, iteration);
                                      iteration -> next -> prev = add;
                                      iteration -> next = add;
                                      if (ptr_p -> prev == nullptr){ //If the changed node is at the beginning of the list initially
                                          ptr -> head = ptr_p -> next;
                                          ptr_p -> next -> prev = nullptr;
                                          delete ptr_p;
                                          ptr_p = nullptr;
                                          ptr = nullptr;
                                      }
                                      else{
                                          ptr_p -> prev -> next = ptr_p -> next;
                                          ptr_p -> next -> prev = ptr_p -> prev;
                                          delete ptr_p;
                                          ptr_p = nullptr;
                                          ptr = nullptr;
                                      }
                                  }
                                }
                                else{ //No change in place is needed
                                    ptr_p = nullptr;
                                    ptr = nullptr;
                                }
                        }
                        else{ //In this case, there is single node in list, no update needed.
                            ptr_p = nullptr;
                            ptr = nullptr;
                        }

                    }
                    else{
                        ptr_p = ptr_p -> next;
                    }
                }
            }
            else{
                ptr = ptr -> down;
            }
        }
    }
    return true;
}

/*
This private function checks whether the given employee is in the list or not. If the employee in the list,
it returns the node of him/her. Otherwise, it returns null.
*/
EmployeeNode *  EmployeeProject2DLL :: isInEmployeeList(string employee_name){
    EmployeeNode * ptr = head_2dll;
    while (ptr != nullptr){
        if (employee_name == ptr -> employee_name){
            return ptr;
        }
        ptr = ptr -> down;
    }
    return nullptr;
}

/*
This function creates a new project node and assigns it to given employee with given information.
Returns false if here is another project with the same priority. Otherwise, it returns true.
*/
bool EmployeeProject2DLL :: assignEmployeeToProject(string employee_name, string project_name, int priority){
    EmployeeNode * ptr = head_2dll;
    if (head_2dll == nullptr){ //If the list is empty.
        ProjectNode * add_project = new ProjectNode(project_name, priority, nullptr, nullptr);
        EmployeeNode * add = new EmployeeNode(employee_name, add_project, add_project, nullptr);
        head_2dll = add;

    }
    else if (isInEmployeeList(employee_name) == nullptr){ //If the given employee is not in the list.
        if (ptr->down == nullptr){ //If there is one employee in list.
            if (ptr -> employee_name > employee_name){
                ProjectNode * add = new ProjectNode(project_name, priority, nullptr, nullptr);
                EmployeeNode * adding = new EmployeeNode(employee_name, add, add, ptr);
                head_2dll = adding;
                ptr -> down = nullptr;
            }
            else{
                ProjectNode * add = new ProjectNode(project_name, priority, nullptr, nullptr);
                EmployeeNode * adding = new EmployeeNode(employee_name, add, add, nullptr);
                head_2dll -> down = adding;
            }
        }
        else{
            if (head_2dll -> employee_name > employee_name){ //If the given employee's name is prior to head's.
                ProjectNode * add = new ProjectNode(project_name, priority, nullptr, nullptr);
                EmployeeNode * adding = new EmployeeNode(employee_name, add, add, ptr);
                head_2dll = adding;
            }
            else{
                while ((ptr -> down != nullptr) && (ptr -> down -> employee_name < employee_name)) {
                    ptr = ptr->down;
                }

                ProjectNode * add = new ProjectNode(project_name, priority, nullptr, nullptr);
                EmployeeNode * adding = new EmployeeNode(employee_name, add, add, ptr -> down);
                ptr-> down = adding;
            }
        }

    }
    else{
        ProjectNode * ptr_p = isInEmployeeList(employee_name) -> head;
        while (ptr_p != nullptr){
            if (ptr_p -> project_priority == priority){
                cout << "The project has not been added because there is another project with the same priority." << endl;
                return false;
            }
            ptr_p = ptr_p->next;
        }

        ProjectNode * ptr_p2= isInEmployeeList(employee_name) -> head;
        if (ptr_p2 -> project_priority > priority) { //Checking the head's priority in comparison to new node.
            ProjectNode *add = new ProjectNode(project_name, priority, ptr_p2, nullptr);
            ptr_p2 -> prev = add;
            isInEmployeeList(employee_name) -> head = add;
        }
        else{
            while (ptr_p2 -> next != nullptr && ptr_p2 -> next -> project_priority < priority){
                ptr_p2 = ptr_p2 -> next;
            }
            if (ptr_p2 -> next == nullptr){ //If the correct position for new node is tail.
                ProjectNode * add = new ProjectNode(project_name, priority, nullptr, ptr_p2);
                ptr_p2 -> next = add;
                isInEmployeeList(employee_name) -> tail = add;
            }
            else{
                ProjectNode * add = new ProjectNode(project_name, priority, ptr_p2-> next, ptr_p2);
                ptr_p2 -> next = add;
                add -> next -> prev = add;
            }
        }

    }
    return true;
}

/*
This function withdraws the given employee from the given project and it returns the priority of that project as a reference parameter.
*/
void EmployeeProject2DLL :: withdrawEmployeeFromProject(string employee_name, string project_name, int & priority){
    EmployeeNode * ptr = head_2dll;
    while (ptr != nullptr){
        if(ptr -> employee_name == employee_name){
            ProjectNode * ptr_p = ptr -> head;
            while (ptr_p != nullptr){
                if (ptr_p -> project_name == project_name){
                    priority = ptr_p -> project_priority;
                    if (ptr_p == ptr->head){ //If the project which will be withdrawn is at the beginning
                        if (ptr_p -> next != nullptr){ //If the project which will be withdrawn is not the single element
                            ptr -> head = ptr_p -> next;
                            ptr_p->next->prev = nullptr;
                            delete ptr_p;
                            ptr_p = nullptr;
                            ptr = nullptr;
                        }
                        else{
                            ptr -> head = nullptr;
                            ptr -> tail = nullptr;
                            delete ptr_p;
                            if (head_2dll -> down == nullptr){ //If there is only one employee in the list.
                                head_2dll = nullptr;
                                delete ptr;
                                ptr = nullptr;
                                ptr_p = nullptr;
                            }
                            else if(head_2dll == ptr){ //If the given employee is at the beginning.
                                head_2dll = head_2dll -> down;
                                delete ptr;
                                ptr = nullptr;
                                ptr_p = nullptr;
                            }
                            else{
                                EmployeeNode * iteration = head_2dll;
                                while (iteration -> down != ptr){
                                    iteration = iteration->down;
                                }

                                iteration->down = ptr->down;
                                delete ptr;
                                ptr = nullptr;
                                ptr_p = nullptr;
                            }
                        }
                    }
                    else if (ptr -> tail == ptr_p){ //If the project which will be withdrawn is at the end
                        ptr_p -> prev -> next = nullptr;
                        ptr -> tail = ptr_p -> prev;
                        delete ptr_p;
                        ptr_p = nullptr;
                        ptr = nullptr;
                    }
                    else
                    {
                        ProjectNode * ptr_p2 = ptr->head;
                        while (ptr_p2 -> next != ptr_p){
                            ptr_p2 = ptr_p2->next;
                        }

                        ptr_p2->next = ptr_p->next;
                        ptr_p2 -> next -> prev = ptr_p-> prev;
                        delete ptr_p;
                        ptr_p = nullptr;
                        ptr = nullptr;
                    }
                }
                else{
                    ptr_p = ptr_p -> next;
                }
            }
        }
        else{
            ptr = ptr -> down;
        }

    }

}

//This function prints the entire list
void EmployeeProject2DLL :: printTheEntireList(){
    EmployeeNode * ptr = head_2dll;
    if (ptr == nullptr){
        cout << "The list is empty." << endl;
    }
    while (ptr != nullptr){
        cout << ptr -> employee_name << ": ";
        ProjectNode * ptr_p = ptr -> head;
        while (ptr_p != nullptr){
            cout << "(" << ptr_p->project_name << ", " << ptr_p -> project_priority << ") ";
            ptr_p = ptr_p -> next;
        }
        cout << endl;
        ptr = ptr -> down;
    }
}

//This function prints the given employee's projects in ascending (if order is 1), or in descending (if order is 0) order.
void EmployeeProject2DLL :: printEmployeeProjects(string employee_name, int order){
    if (head_2dll == nullptr){
        cout << "There are no employees in the list." << endl;
    }
    else if (isInEmployeeList(employee_name) == nullptr){
        cout << "The employee is not in the list." << endl;
    }
    else {
        EmployeeNode *ptr = head_2dll;
        while (ptr != nullptr) {
            if (employee_name == ptr->employee_name) {
                if (order == 1) {
                    ProjectNode *ptr_p = ptr->head;
                    while (ptr_p != nullptr) {
                        cout << "(" << ptr_p->project_name << ", " << ptr_p->project_priority << ") ";
                        ptr_p = ptr_p->next;
                    }
                    cout << endl;
                } else if (order == 0) {
                    ProjectNode *ptr_t = ptr->tail;
                    while (ptr_t != nullptr) {
                        cout << "(" << ptr_t->project_name << ", " << ptr_t->project_priority << ") ";
                        ptr_t = ptr_t->prev;
                    }
                    cout << endl;
                }
            }
            ptr = ptr -> down;
        }
    }
}

//This function reverses the last operation using the information which comes from the stack.
void EmployeeProject2DLL :: undo(char operation_type, string employee_name, string project_name, int priority){
    if (operation_type == 'w'){
        cout << "Undoing the withdrawal of a project." << endl;
        assignEmployeeToProject(employee_name,project_name,priority);
    }
    else if (operation_type == 'u'){
        cout << "Undoing the update of a project priority." << endl;
        updateProjectPriority(employee_name, project_name,priority);
    }
    else if (operation_type == 'a'){
        cout << "Undoing the assignment of a project." << endl;
        withdrawEmployeeFromProject(employee_name,project_name,priority);
    }

}

//This function clears the list.
void EmployeeProject2DLL :: clear(){
    EmployeeNode * ptr = head_2dll;
    while (ptr != nullptr){
        ProjectNode*temp;
        while (ptr -> head != nullptr){
            temp = ptr -> head -> next;
            delete ptr -> head;
            ptr -> head = temp;
        }
    ptr = ptr -> down;
    }
    EmployeeNode * temp2 ;
    while (head_2dll!= nullptr){
        temp2 = head_2dll -> down;
        delete head_2dll;
        head_2dll = temp2;
    }
}