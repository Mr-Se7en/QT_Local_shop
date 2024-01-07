//// salesmodel.cpp
// salesmodel.cpp

#include "SalesTreeModel.h"

SalesTreeModel::SalesTreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    //root item called "Log"
    DateItem rootItem;
    rootItem.date = QDateTime(); // Set an arbitrary date for the root
    dates.append(rootItem);
}

SalesTreeModel::~SalesTreeModel() {}

void SalesTreeModel::addPurchase(const QDateTime &date, const QString &customer, const QString &product, double amount)
{
    DateItem *dateItem = getDateItem(date);
    CustomerItem *customerItem = getCustomerItem(dateItem, customer);

    beginInsertRows(createIndex(dateItem->date.daysTo(date), 0, dateItem), customerItem->products.size(), customerItem->products.size());
    customerItem->products.append({product, amount});
    endInsertRows();
}

QModelIndex SalesTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {
        // Top-level items (Log)
        if (row < dates.size())
            return createIndex(row, column, &dates[row]);
    } else if (parent.isValid() && !parent.parent().isValid()) {
        // Second-level items (Date)
        DateItem *dateItem = static_cast<DateItem *>(parent.internalPointer());
        if (row < dateItem->customers.size())
            return createIndex(row, column, &dateItem->customers[row]);
    } else if (parent.isValid() && parent.parent().isValid()) {
        // Third-level items (Product)
        DateItem *dateItem = static_cast<DateItem *>(parent.parent().internalPointer());
        if (row < dateItem->customers[parent.row()].products.size())
            return createIndex(row, column, &dateItem->customers[parent.row()].products[row]);
    }

    return QModelIndex();
}

QModelIndex SalesTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    if (index.internalPointer() == nullptr)
        return QModelIndex(); // Top-level items have no parent

    if (DateItem *dateItem = static_cast<DateItem *>(index.internalPointer())) {
        return QModelIndex();
    } else if (CustomerItem *customerItem = static_cast<CustomerItem *>(index.internalPointer())) {
        DateItem *dateItem = static_cast<DateItem *>(index.parent().internalPointer());
        return createIndex(dateItem->date.daysTo(dateItem->date), 0, dateItem);
    } else if (ProductItem *productItem = static_cast<ProductItem *>(index.internalPointer())) {
        DateItem *dateItem = static_cast<DateItem *>(index.parent().parent().internalPointer());
        CustomerItem *customerItem = &dateItem->customers[index.parent().row()];
        return createIndex(customerItem->products.indexOf(*productItem), 0, customerItem);
    }

    return QModelIndex();
}

int SalesTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        // Top-level items (Log)
        return dates.size();
    } else if (!parent.parent().isValid()) {
        // Second-level items (Date)
        DateItem *dateItem = static_cast<DateItem *>(parent.internalPointer());
        return dateItem->customers.size();
    } else if (parent.parent().isValid()) {
        // Third-level items (Product)
        DateItem *dateItem = static_cast<DateItem *>(parent.parent().internalPointer());
        CustomerItem *customerItem = &dateItem->customers[parent.row()];
        return customerItem->products.size();
    }

    return 0;
}

int SalesTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2; // Customer/Product and Amount
}

QVariant SalesTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (DateItem *dateItem = static_cast<DateItem *>(index.internalPointer())) {
            // Display Date or "Log" for the root
            return (dateItem->date == QDateTime()) ? "Log" : dateItem->date.toString(Qt::ISODate);
        } else if (CustomerItem *customerItem = static_cast<CustomerItem *>(index.internalPointer())) {
            // Display Customer name
            return customerItem->name;
        } else if (ProductItem *productItem = static_cast<ProductItem *>(index.internalPointer())) {
            // Display Product name or Amount
            if (index.column() == 0)
                return productItem->name;
            else if (index.column() == 1)
                return productItem->amount;
        }
    }

    return QVariant();
}
SalesTreeModel::DateItem *SalesTreeModel::getDateItem(const QDateTime &date)
{
    for (auto &dateItem : dates) {
        if (dateItem.date == date) {
            return &dateItem;
        }
    }

    // Date doesn't exist, add a new DateItem
    beginInsertRows(QModelIndex(), dates.size(), dates.size());
    dates.append({date, {}});
    endInsertRows();

    return &dates.last();
}

SalesTreeModel::CustomerItem *SalesTreeModel::getCustomerItem(SalesTreeModel::DateItem *dateItem, const QString &customer)
{
    for (auto &customerItem : dateItem->customers) {
        if (customerItem.name == customer) {
            return &customerItem;
        }
    }

    // Customer doesn't exist, add a new CustomerItem
    beginInsertRows(createIndex(dateItem->date.daysTo(dateItem->date), 0, dateItem), dateItem->customers.size(), dateItem->customers.size());
    dateItem->customers.append({customer, {}});
    endInsertRows();

    return &dateItem->customers.last();
}

/*
#include "SalesTreeModel.h"
#include <QVBoxLayout>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QPushButton>

SalesWidget::SalesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(3);
    treeWidget->setHeaderLabels({"Date", "Customer", "Product/Amount"});
    layout->addWidget(treeWidget);

    QPushButton *addButton = new QPushButton("Add Purchase", this);
    connect(addButton, &QPushButton::clicked, this, &SalesWidget::addPurchase);
    layout->addWidget(addButton);
}

void SalesWidget::addPurchase()
{
    QDateTime date = QDateTime::currentDateTime();
    QString customer = "John Doe";
    QString product = "banana";
    double amount = 7.0;

    addTreeRoot(date);
    addTreeChild(treeWidget->topLevelItem(0), customer, product, amount);
}

void SalesWidget::addTreeRoot(const QDateTime &date)
{
    QTreeWidgetItem *rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, date.toString(Qt::ISODate));
}

void SalesWidget::addTreeChild(QTreeWidgetItem *parent, const QString &customer, const QString &product, double amount)
{
    QTreeWidgetItem *childItem = new QTreeWidgetItem(parent);
    childItem->setText(1, customer);
    childItem->setText(2, QString("%1 (%2)").arg(product).arg(amount));
}*/
