#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QMetaType>
#include <QModelIndex>
#include <QStringList>
#include <QVariant>
#include <QVector>

class Model : public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef QStringList Schema;
    typedef QVector<QMetaType::Type> Types;
    typedef QVector<QVariant> Row;
    typedef QVector<Row> Rows;

    Schema schema;
    Types types;
    Rows rows;

    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

#endif // TABLEMODEL_H
