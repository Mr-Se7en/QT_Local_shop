// customertablemodel.h
#ifndef CUSTOMERTABLEMODEL_H
#define CUSTOMERTABLEMODEL_H

#include "customer.h"
#include <QAbstractTableModel>
#include <QVector>
#include <QFile>
#include <QTextStream>

class CustomerTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    CustomerTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Add a customer
    void addCustomer(const CUSTOMER &customer);

    // Update a customer
    bool updateCustomer(int row, const CUSTOMER &customer);

    // Remove a customer
    bool removeCustomer(int row);

    int findCustomerIndex(const QString &customerId) const;
    bool checkAndHandleDuplication(const CUSTOMER &customer, double totalAmountPurchased, double amountPaid);

    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);
    bool addCustomer(const CUSTOMER &newCustomer, double totalAmountPurchased, double amountPaid);
    CUSTOMER getCustomer(int row) const;
private:
    QList<CUSTOMER> customerList;
    void adjustDebtAndCredit(CUSTOMER &customer);
};

#endif // CUSTOMERTABLEMODEL_H
