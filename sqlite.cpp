#include "sqlite.h"

SQLite::SQLite(const QString &fileName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    db.open();
}

SQLite::~SQLite()
{
    db.close();
}

QStringList SQLite::tableNames() const
{
    return db.tables();
}

void SQLite::read(const QString &tableName, Model *model) const
{

}

void SQLite::write(const QString &tableName, const Model *model)
{

}
