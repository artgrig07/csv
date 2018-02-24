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
    // Читаем схему
    model->schema << decodeSchema(readRow());

    // Читаем строки
    while (!stream->atEnd()) model->rows << readRow();

    // Вычисляем типы
    model->types << calculateTypes(model);
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
    writeRow(encodeSchema(model->schema));

    // Записываем строки
    for (const Model::Row &row : model->rows) writeRow(row);
}


Model::Types CSV::calculateTypes(Model *model) const
{
    const int columnCount = model->schema.count();

    // Инициализируем список типов
    Model::Types types;
    for (int i = 0; i < columnCount; i++) types << QMetaType::LongLong;

    // Обходим все строки
    for (const Model::Row &row : model->rows) {
        // Обходим все колонки
        for (int i = 0; i < columnCount; i++) {
            // Получаем тип текущего поля
            const QMetaType::Type fieldType = (QMetaType::Type)row.at(i).userType();

            // Обновляем тип колонки
            // LongLong < Double < String
            if (fieldType > types.at(i)) types.replace(i, fieldType);
        }
    }

    return types;
}


Model::Row CSV::readRow() const
{
    Model::Row row;
    PARSING_STATE state = PARSING_STATE::NEW_LINE;
    QString str;
    while (!stream->atEnd() && state != PARSING_STATE::END_LINE) {
        QChar ch;
        *stream >> ch;

        switch (state) {
            case PARSING_STATE::NEW_LINE:
                if (ch == ',') {
                    row << QString();
                    state = PARSING_STATE::NEW_FIELD;
                } else if (ch == '"') {
                    str.append('"');
                    state = PARSING_STATE::QUOTED_FIELD;
                } else if (ch == '\n') {
                    state = PARSING_STATE::END_LINE;
                } else {
                    str.append(ch);
                    state = PARSING_STATE::SIMPLE_FIELD;
                }
                break;

            case PARSING_STATE::NEW_FIELD:
                if (ch == ',') {
                    row << QString();
                    state = PARSING_STATE::NEW_FIELD;
                } else if (ch == '"') {
                    str.append('"');
                    state = PARSING_STATE::QUOTED_FIELD;
                } else if (ch == '\n') {
                    row << QString();
                    state = PARSING_STATE::END_LINE;
                } else {
                    str.append(ch);
                    state = PARSING_STATE::SIMPLE_FIELD;
                }
                break;

            case PARSING_STATE::SIMPLE_FIELD:
                if (ch == ',') {
                    row << decodeValue(str);
                    str.clear();
                    state = PARSING_STATE::NEW_FIELD;
                } else if (ch == '\n') {
                    row << decodeValue(str);
                    state = PARSING_STATE::END_LINE;
                } else {
                    str.append(ch);
                }
                break;

            case PARSING_STATE::QUOTED_FIELD:
                if (ch == '"') {
                    str.append('"');
                    state = PARSING_STATE::QUOTED_QUOTE;
                } else {
                    str.append(ch);
                }
                break;

            case PARSING_STATE::QUOTED_QUOTE:
                if (ch == '"') {
                    state = PARSING_STATE::QUOTED_FIELD;
                } else if (ch == ',') {
                    row << decodeValue(str);
                    str.clear();
                    state = PARSING_STATE::NEW_FIELD;
                } else if (ch == '\n') {
                    row << decodeValue(str);
                    state = PARSING_STATE::END_LINE;
                }
                break;

            default:
                break;
        }
    }

    return row;
}

void CSV::writeRow(const Model::Row &row)
{
    QStringList line;
    for (const QVariant &value : row) line << encodeValue(value);
    *stream << line.join(',') << '\n';
}


Model::Row CSV::encodeSchema(const Model::Schema &schema) const
{
    Model::Row row;
    for (const QString &str : schema) row << str;
    return row;
}

Model::Schema CSV::decodeSchema(const Model::Row &row) const
{
    Model::Schema schema;
    for (const QVariant &value : row) schema << value.toString();
    return schema;
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
