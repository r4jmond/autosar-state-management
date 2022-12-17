#include "gtest/gtest.h"
#include "Employee.h"


TEST(blaTest, test1)
{
    Employee employee = Employee(15, "Foobar");
    EXPECT_EQ(employee.getAge(), 15);
}

