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
    /**
     * Constructs a new SQLite object with the given fileName
     *
     * \param[in] fileName SQLite file name
     */
    SQLite(const QString &fileName);

    ~SQLite();

    QStringList tableNames() const;

    /**
     * Reads SQLite table into model
     *
     * \param[in] tableName SQLite table name
     * \param[out] model Pointer to model where data from SQLite table will be stored
     */
    void read(const QString &tableName, Model *model) const;

    /**
     * Reads SQLite table into model
     *
     * \param[in] tableName SQLite table name
     * \return Pointer to model where data from SQLite table will be stored
     */
    Model read(const QString &tableName) const;

    /**
     * Writes SQLite table from model
     *
     * \param[in] tableName SQLite table name
     * \param[in] model Pointer to model where data for SQLite table is stored
     */
    void write(const QString &tableName, const Model *model);

private:
    QSqlDatabase db;

    QString encodeType(const QMetaType::Type type) const;
    QString encodeValue(const QVariant &value) const;
};

#endif // SQLITE_H
