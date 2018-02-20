#include "model.h"

void Model::update()
{
    emit dataChanged(createIndex(0, 0), createIndex(rowCount(), columnCount()));
    emit layoutChanged();
}

void Model::clear()
{
    beginResetModel();
    schema.clear();
    types.clear();
    rows.clear();
    endResetModel();
}


int Model::rowCount(const QModelIndex &) const
{
    return rows.count();
}

int Model::columnCount(const QModelIndex &) const
{
    return schema.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (rows.empty()) return QVariant();

    return rows.at(index.row()).at(index.column());
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation != Qt::Horizontal) return QVariant();
    if (section >= schema.count()) return QVariant();

    return QVariant(schema.at(section));
}
