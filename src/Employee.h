#include <iostream>


class Employee
{
    private:
    int age;
    std::string name;

public:
    Employee(int age_, std::string name_);
    int getAge(void);
};
