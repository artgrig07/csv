#include "model.h"

int Model::rowCount(const QModelIndex &parent) const
{
    // TODO
    return 0;
}

int Model::columnCount(const QModelIndex &parent) const
{
    // TODO
    return 0;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    // TODO
    return QVariant();
}

void Model::clear()
{
    beginResetModel();
    // TODO
    endResetModel();
}
