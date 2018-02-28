#include <QTest>

#include "testcsv.h"

int main(int argc, char *argv[]) {
   int status = 0;

   TestCSV csv;
   status |= QTest::qExec(&csv, argc, argv);

   return status;
}
