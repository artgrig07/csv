#include "csv.h"

CSV::CSV(const QString &fileName) :
    file(fileName)
{
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    stream = new QTextStream(&file);
    stream->setCodec("UTF-8");
}

CSV::~CSV()
{
    delete stream;
    file.close();
}

void CSV::read(Model *model) const
{
    // TODO
}

Model CSV::read() const
{
    Model model;
    read(&model);
    return model;
}

void CSV::write(const Model *model)
{
    // Записываем схему
    writeRow(decodeSchema(model->schema));

    // Записываем строки
    for (const Model::Row &row : model->rows) writeRow(row);
}


void CSV::writeRow(const Model::Row &row)
{
    QStringList line;
    for (const QVariant &value : row) line << encodeValue(value);
    *stream << line.join(',') << '\n';
}


Model::Schema CSV::encodeSchema(const Model::Row &row) const
{
    Model::Schema schema;
    for (const QVariant &value : row) schema << value.toString();
    return schema;
}

Model::Row CSV::decodeSchema(const Model::Schema &schema) const
{
    Model::Row row;
    for (const QString &str : schema) row << str;
    return row;
}

QString CSV::encodeValue(const QVariant &value) const
{
    return escapeStr(value.toString());
}

QVariant CSV::decodeValue(const QString &str) const
{
    // Пытаемся получить LongLong
    bool longLongOk;
    long long longLongField = str.toLongLong(&longLongOk);
    if (longLongOk) return QVariant(longLongField);

    // Пытаемся получить Double
    bool doubleOk;
    double doubleField = str.toDouble(&doubleOk);
    if (doubleOk) return QVariant(doubleField);

    return unescapeStr(str);
}

QString CSV::escapeStr(QString str) const
{
    if (str.indexOf(',') != -1 || str.indexOf('\n') != -1 || str.indexOf('"') != -1) {
        str.replace("\"", "\"\"").prepend('"').append('"');
    }

    return str;
}

QString CSV::unescapeStr(QString str) const
{
    if (str.at(0) == '"') {
        str.mid(1, str.length() - 2).replace("\"\"", "\"");
    }

    return str;
}
