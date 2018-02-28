#ifndef TESTCSV_H
#define TESTCSV_H

#include <QFile>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QtTest>

#include "../app/model.h"
#include "../app/csv.h"

class TestCSV : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void write();
    void read();

private:
    QString fileName;
    Model::Schema schema;
    Model::Types types;
    Model::Rows rows;
};

#endif // TESTCSV_H
