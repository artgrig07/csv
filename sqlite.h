#ifndef SQLITE_H
#define SQLITE_H

#include <QString>
#include <QStringList>
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
};

#endif // SQLITE_H
