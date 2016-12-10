#include <QtTest/QtTest>
#include "databasetest.h"

int main(int argc, char *argv[])
{
    int ret = 0;
    DatabaseTest databaseTest;
    ret += QTest::qExec(&databaseTest, argc, argv);

    return ret;
}
