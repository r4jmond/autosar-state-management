#include "gtest/gtest.h"
#include "Employee.h"


TEST(testSuite1, test1)
{
    Employee employee = Employee(15, "Foobar");
    EXPECT_EQ(employee.getAge(), 25);
}

