#ifndef SQLITE_H
#define SQLITE_H

#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtSql>

#include "model.h"

class SQLite
{
public:
    SQLite(const QString &fileName);
    ~SQLite();

    QStringList tableNames() const;
    void read(const QString &tableName, Model *model) const;
    Model read(const QString &tableName) const;
    void write(const QString &tableName, const Model *model);

private:
    QSqlDatabase db;

    QString encodeType(const QMetaType::Type type) const;
    QString encodeValue(const QVariant &value) const;
};

#endif // SQLITE_H
