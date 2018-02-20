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
    writeSchema(model->schema);
    writeRows(model->rows);
}


void CSV::writeSchema(const Model::Schema &schema)
{
    QStringList line;
    for (const QString &column : schema) {
        line << encodeValue(column);
    }

    *stream << line.join(',') << '\n';
}

void CSV::writeRows(const Model::Rows &rows)
{
    for (const Model::Row &row : rows) {
        writeRow(row);
    }
}

void CSV::writeRow(const Model::Row &row)
{
    QStringList line;
    for (const QVariant &value : row) {
        line << encodeValue(value);
    }

    *stream << line.join(',') << '\n';
}


QString CSV::encodeValue(const QVariant &value)
{
    QString str = value.toString();

    // Экранируем строку содержащую специальные символы
    if (str.indexOf(',') != -1 || str.indexOf('\n') != -1 || str.indexOf('"') != -1) {
        return "\"" + QString(str).replace('"', "\"\"") + "\"";
    }

    return str;
}
