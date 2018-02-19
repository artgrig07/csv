#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>
#include <Qt>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void clear();
};

#endif // TABLEMODEL_H
