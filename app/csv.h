#ifndef CSV_H
#define CSV_H

#include <QChar>
#include <QFile>
#include <QIODevice>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVariant>

#include "model.h"

class CSV
{
public:
    /**
     * Constructs a new CSV object with the given fileName
     *
     * \param[in] fileName CSV file name
     */
    CSV(const QString &fileName);

    ~CSV();

    /**
     * Reads CSV file into model
     *
     * \param[out] model Pointer to model where data from CSV file will be stored
     */
    void read(Model *model) const;

    /**
     * Reads CSV file into model
     *
     * \return Pointer to model where data from CSV file will be stored
     */
    Model read() const;

    /**
     * Writes CSV file from model
     *
     * \param[in] model Pointer to model where data for CSV file is stored
     */
    void write(const Model *model);

private:
    enum PARSING_STATE {
        NEW_FIELD,
        SIMPLE_FIELD,
        QUOTED_FIELD,
        QUOTED_QUOTE,
        END_LINE,
    };

    QFile file;
    QTextStream *stream;

    Model::Row readRow() const;
    void writeRow(const Model::Row &row);

    Model::Types calculateTypes(Model *model) const;

    Model::Row encodeSchema(const Model::Schema &schema) const;
    Model::Schema decodeSchema(const Model::Row &row) const;

    QString encodeValue(const QVariant &value) const;
    QVariant decodeValue(const QString &str) const;

    QString escapeStr(QString str) const;
};

#endif // CSV_H
