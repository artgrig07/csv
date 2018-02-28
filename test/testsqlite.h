#ifndef TESTSQLITE_H
#define TESTSQLITE_H

#include <QFile>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QtTest>

#include "../app/model.h"
#include "../app/sqlite.h"

class TestSQLite : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void write();
    void read();

private:
    SQLite *db;
    QString tableName;
    Model::Schema schema;
    Model::Types types;
    Model::Rows rows;
};

#endif // TESTSQLITE_H
