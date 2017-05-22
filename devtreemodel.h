#ifndef DEVTREEMODEL_H
#define DEVTREEMODEL_H

#include <QAbstractItemModel>

class devTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit devTreeModel(QObject *parent = 0);
    ~devTreeModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
};

#endif // DEVTREEMODEL_H
