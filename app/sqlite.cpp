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
    const int columnCount = record.count();

    // Заполняем схему
    for (int i = 0; i < columnCount; i++)
    {
        model->schema.push_back(record.fieldName(i));
    }

    // Заполняем типы
    for (int i = 0; i < columnCount; i++)
    {
        QMetaType::Type type = (QMetaType::Type)record.field(i).type();
        if (type == QMetaType::Int) type = QMetaType::LongLong;

        model->types.push_back(type);
    }

    // Заполняем строки
    QSqlQuery query(QString("SELECT * FROM %1;").arg(tableName));
    while (query.next())
    {
        Model::Row row;
        for (int i = 0; i < columnCount; i++)
        {
            row.push_back(query.value(i));
        }

        model->rows.push_back(row);
    }
}

Model SQLite::read(const QString &tableName) const
{
    Model model;
    read(tableName, &model);
    return model;
}

void SQLite::write(const QString &tableName, const Model *model)
{
    const int columnCount = model->schema.count();

    // Удаляем существующую таблицу
    db.exec(QString("DROP TABLE IF EXISTS %1;").arg(tableName));

    // Создаем таблицу
    QStringList schema;
    for (int i = 0; i < columnCount; i++)
    {
        const QString &type = encodeType(model->types.at(i));
        const QString &columnName = model->schema.at(i);
        schema.append(QString("%1 %2").arg(columnName, type));
    }
    db.exec(QString("CREATE TABLE %1 (%2);").arg(tableName).arg(schema.join(", ")));

    // Загружаем данные в таблицу
    db.transaction();
    for (const Model::Row &row: model->rows)
    {
        QStringList line;
        for (const QVariant &value : row)
        {
            line << encodeValue(value);
        }

        db.exec(QString("INSERT INTO %1 VALUES (%2)").arg(tableName).arg(line.join(", ")));
    }
    db.commit();
}


QString SQLite::encodeType(const QMetaType::Type type) const
{
    if (type == QMetaType::LongLong) return "INTEGER";
    if (type == QMetaType::Double) return "REAL";
    return "TEXT";
}

QString SQLite::encodeValue(const QVariant &value) const
{
    return value.toString().replace("\"", "\"\"").prepend('"').append('"');
}
