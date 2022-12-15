#include "Employee.h"


Employee::Employee(int age_, std::string name_)
{
    age = age_;
    name = name_;
};


int Employee::getAge(void)
{
    return age;
};
