#include "testcsv.h"

void TestCSV::initTestCase()
{
    fileName = "test.csv";
    schema << Model::Schema({"col1", "col2", "col3"});
    types << Model::Types({QMetaType::LongLong, QMetaType::Double, QMetaType::QString});
    for (qlonglong i = 0; i < 7; i++) rows << Model::Row({i, i * .1, QString("ab,cd\"ef\ngh")});
}

void TestCSV::cleanupTestCase()
{
    QFile file(fileName);
    file.remove();
}


void TestCSV::write()
{
    CSV csv(fileName);

    Model model;
    model.schema << schema;
    model.types << types;
    model.rows << rows;
    csv.write(&model);
}

void TestCSV::read()
{
    CSV csv(fileName);

    Model model;
    csv.read(&model);

    QVERIFY(model.schema == schema);
    QVERIFY(model.types == types);
    QVERIFY(model.rows == rows);
}
