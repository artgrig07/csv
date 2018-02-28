#include <QTest>

#include "testcsv.h"
#include "testsqlite.h"

int main(int argc, char *argv[])
{
    int status = 0;

    TestCSV csv;
    status |= QTest::qExec(&csv, argc, argv);

    TestSQLite sqlite;
    status |= QTest::qExec(&sqlite, argc, argv);

    return status;
}
