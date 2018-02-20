#ifndef CSV_H
#define CSV_H

#include <QFile>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVariant>

#include "model.h"

class CSV
{
public:
    CSV(const QString &fileName);
    ~CSV();

    void read(Model *model) const;
    Model read() const;
    void write(const Model *model);

private:
    QFile file;
    QTextStream *stream;

    void writeRow(const Model::Row &row);

    Model::Schema encodeSchema(const Model::Row &row) const;
    Model::Row decodeSchema(const Model::Schema &schema) const;

    QString encodeValue(const QVariant &value) const;
    QVariant decodeValue(const QString &str) const;

    QString escapeStr(QString str) const;
    QString unescapeStr(QString str) const;
};

#endif // CSV_H
