#include "testsqlite.h"

void TestSQLite::initTestCase()
{
    db = new SQLite(":memory");
    tableName = "test";
    schema << Model::Schema({"col1", "col2", "col3"});
    types << Model::Types({QMetaType::LongLong, QMetaType::Double, QMetaType::QString});
    for (qlonglong i = 0; i < 7; i++) rows << Model::Row({i, i * .1, QString("ab;cd\"ef\ngh")});
}

void TestSQLite::cleanupTestCase()
{
    delete db;
}


void TestSQLite::write()
{
    Model model;
    model.schema << schema;
    model.types << types;
    model.rows << rows;
    db->write(tableName, &model);
}

void TestSQLite::read()
{
    Model model;
    db->read(tableName, &model);

    QVERIFY(model.schema == schema);
    QVERIFY(model.types == types);
    QVERIFY(model.rows == rows);
}
