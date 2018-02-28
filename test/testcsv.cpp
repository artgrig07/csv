#include "testcsv.h"

void TestCSV::initTestCase()
{}

void TestCSV::cleanupTestCase()
{}


void TestCSV::readWrite()
{
    QString fileName = "test.csv";

    Model sourceModel;
    sourceModel.schema << Model::Schema({"col1", "col2", "col3"});
    sourceModel.types << Model::Types({QMetaType::LongLong, QMetaType::Double, QMetaType::QString});
    for (qlonglong i = 0; i < 7; i++) sourceModel.rows << Model::Row({i, i * .1, QString("ab;cd\"ef\ngh")});

    Model resultModel;

    {
        CSV csv(fileName);
        csv.write(&sourceModel);
    }

    {
        CSV csv(fileName);
        csv.read(&resultModel);
    }

    QVERIFY(sourceModel.schema == resultModel.schema);
    QVERIFY(sourceModel.types == resultModel.types);
    QVERIFY(sourceModel.rows == resultModel.rows);

    QFile file(fileName);
    file.remove();
}
