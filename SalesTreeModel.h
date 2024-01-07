//// salesmodel.h
#ifndef SALESMODEL_H
#define SALESMODEL_H

#include <QAbstractItemModel>
#include <QDateTime>
#include <QList>
#include <QString>

class SalesTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SalesTreeModel(QObject *parent = nullptr);
    ~SalesTreeModel();

    // Function to add a customer purchase
    void addPurchase(const QDateTime &date, const QString &customer, const QString &product, double amount);

    // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    struct ProductItem {
        QString name;
        double amount;
        bool operator==(const ProductItem &other) const {
            return name == other.name && amount == other.amount;
        }
    };

    struct CustomerItem {
        QString name;
        QList<ProductItem> products;
    };

    struct DateItem {
        QDateTime date;
        QList<CustomerItem> customers;
    };

    QList<DateItem> dates;

    DateItem *getDateItem(const QDateTime &date);
    CustomerItem *getCustomerItem(DateItem *dateItem, const QString &customer);
};
#endif // SALESWIDGET_H
