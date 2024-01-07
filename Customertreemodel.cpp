#include "CustomerTreeModel.h"

CustomerTreeModel::CustomerTreeModel(QObject *parent)
    : QStandardItemModel(parent), rootItem(nullptr)
{
    setHorizontalHeaderLabels(QStringList() << "Details");
}

void CustomerTreeModel::setupModel(const QVector<CUSTOMER> &customers)
{
    rootItem = new QStandardItem("Customers");
    appendRow(rootItem);

    for (const CUSTOMER &customer : customers)
    {
        addCustomerToTree(customer);
    }
}

void CustomerTreeModel::addCustomerToTree(const CUSTOMER &customer)
{
    QStandardItem *customerItem = new QStandardItem(customer.getName());
    customerItem->setData(QVariant::fromValue(customer), Qt::UserRole); // Store customer data in item's data

    // Add child items for each property
    customerItem->appendRow(new QStandardItem("ID: " + customer.getId()));
    customerItem->appendRow(new QStandardItem("Credit Amount: " + QString::number(customer.getCreditAmount())));
    customerItem->appendRow(new QStandardItem("Debit Amount: " + QString::number(customer.getDebitAmount())));
    customerItem->appendRow(new QStandardItem("Contact Number: " + customer.getContactNumber()));
    customerItem->appendRow(new QStandardItem("Address: " + customer.getAddress()));

//    addProductToTree(getProductsForCustomer(customer), customerItem);

    rootItem->appendRow(customerItem);
}

void CustomerTreeModel::addProductToTree(const QList<PRODUCT> &products, QStandardItem *customerItem)
{
    for (const PRODUCT &product : products)
    {
        QStandardItem *productItem = new QStandardItem(product.getproductName());
        productItem->setData(QVariant::fromValue(product), Qt::UserRole); // Store product data in item's data

        customerItem->appendRow(productItem);
    }
}

void CustomerTreeModel::onItemClicked(const QModelIndex &index)
{
    QStandardItem *item = itemFromIndex(index);
    if (!item)
        return;

    if (item->data(Qt::UserRole).canConvert<CUSTOMER>())
    {
        CUSTOMER customer = item->data(Qt::UserRole).value<CUSTOMER>();
        emit customerSelected(customer);
    }
    else if (item->data(Qt::UserRole).canConvert<PRODUCT>())
    {
        PRODUCT product = item->data(Qt::UserRole).value<PRODUCT>();
        emit productSelected(product);
    }
}
