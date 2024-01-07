#ifndef CUSTOMERTREEMODEL_H
#define CUSTOMERTREEMODEL_H

#include <QStandardItemModel>
#include "ProductTableModel.h"
#include "customer.h"

class CustomerTreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit CustomerTreeModel(QObject *parent = nullptr);

    void setupModel(const QVector<CUSTOMER> &customers);

private:
    void addCustomerToTree(const CUSTOMER &customer);
    void addProductToTree(const QList<PRODUCT> &products, QStandardItem *customerItem);

signals:
    void customerSelected(const CUSTOMER &customer);
    void productSelected(const PRODUCT &product);

public slots:
    void onItemClicked(const QModelIndex &index);

private:
    QStandardItem *rootItem;
};

#endif // CUSTOMERTREEMODEL_H
