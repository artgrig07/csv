#include "tablemodel.h"

TableModel::TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    // TODO
    return 0;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    // TODO
    return 0;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    // TODO
    return QVariant();
}

void TableModel::clear()
{
    beginResetModel();
    // TODO
    endResetModel();
}
