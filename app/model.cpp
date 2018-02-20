#include "model.h"

Model::Model(QObject *parent) :
    QAbstractTableModel(parent)
{}

Model::Model(const Model &model) :
    schema(model.schema),
    types(model.types),
    rows(model.rows)
{
    update();
}

void Model::update()
{
    emit layoutChanged();
}

void Model::clear()
{
    schema.clear();
    types.clear();
    rows.clear();

    update();
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
