#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QMetaType>
#include <QModelIndex>
#include <QStringList>
#include <QVariant>
#include <QVariantList>

class Model : public QAbstractTableModel
{
    Q_OBJECT

public:
    Model(QObject *parent = Q_NULLPTR);
    Model(const Model &model);

    typedef QStringList Schema;
    typedef QList<QMetaType::Type> Types;
    typedef QVariantList Row;
    typedef QList<Row> Rows;

    Schema schema;
    Types types;
    Rows rows;

    /**
     * Updates table view
     */
    void update();

    /**
     * Clears data and updates table view
     */
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

#endif // MODEL_H
