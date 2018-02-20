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

    void writeSchema(const Model::Schema &schema);
    void writeRows(const Model::Rows &rows);
    void writeRow(const Model::Row &row);

    QString encodeValue(const QVariant &value);
};

#endif // CSV_H
