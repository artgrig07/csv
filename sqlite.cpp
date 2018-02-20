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
    QSqlRecord record = db.record(tableName);
    int columnCount = record.count();

    // Заполняем схему
    for (int i = 0; i < columnCount; i++) {
        model->schema.push_back(record.fieldName(i));
    }

    // Заполняем типы
    for (int i = 0; i < columnCount; i++) {
        QMetaType::Type type = (QMetaType::Type)record.field(i).type();
        if (type == QMetaType::Int) type = QMetaType::LongLong;

        model->types.push_back(type);
    }

    // Заполняем строки
    QSqlQuery query(QString("SELECT * FROM %1;").arg(tableName));
    while (query.next()) {
        Model::Row row;
        for (int i = 0; i < columnCount; i++) {
            row.push_back(query.value(i));
        }

        model->rows.push_back(row);
    }
}

void SQLite::write(const QString &tableName, const Model *model)
{

}
