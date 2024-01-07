// In your implementation file (e.g., SalesWidget.cpp)
#include "saleswidget.h"
#include <QVBoxLayout>

SalesWidget::SalesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    treeWidget = new QTreeWidget(this);
    treeWidget->setColumnCount(3);
    treeWidget->setHeaderLabels({"Date", "Customer", "Product/Amount"});
    layout->addWidget(treeWidget);

    //the Log root item
    addLogRoot();
}

void SalesWidget::addLogRoot()
{
    QTreeWidgetItem *logRoot = new QTreeWidgetItem(treeWidget);
    logRoot->setText(0, "Log");
}

void SalesWidget::addDate(const QDate &date)
{
    QTreeWidgetItem *logRoot = treeWidget->topLevelItem(0); //Log is the first top-level item
    QTreeWidgetItem *dateItem = new QTreeWidgetItem(logRoot);
    dateItem->setText(0, date.toString(Qt::ISODate));
}

QTreeWidgetItem *SalesWidget::findOrCreateDateItem(const QDate &date)
{
    QTreeWidgetItem *logRoot = treeWidget->topLevelItem(0); //Log is the first top-level item

    // Find existing date item
    for (int i = 0; i < logRoot->childCount(); ++i) {
        QTreeWidgetItem *item = logRoot->child(i);
        if (item->text(0) == date.toString(Qt::ISODate)) {
            return item;
        }
    }

    // Create a new date item if not found
    QTreeWidgetItem *newDateItem = new QTreeWidgetItem(logRoot);
    newDateItem->setText(0, date.toString(Qt::ISODate));
    return newDateItem;
}

void SalesWidget::addPurchase(const QDate &date, const QString &customer, const QVector<QString> &products, const QVector<double> &amounts)
{
    QTreeWidgetItem *dateItem = findOrCreateDateItem(date);

    // Find or create a customer item under the date
    QTreeWidgetItem *customerItem = nullptr;
    for (int i = 0; i < dateItem->childCount(); ++i) {
        QTreeWidgetItem *item = dateItem->child(i);
        if (item->text(1) == customer) {
            customerItem = item;
            break;
        }
    }

    if (!customerItem) {
        customerItem = new QTreeWidgetItem(dateItem);
        customerItem->setText(1, customer);
    }

    // Add products as subitems under the customer
    for (int i = 0; i < products.size(); ++i) {
        QTreeWidgetItem *productItem = new QTreeWidgetItem(customerItem);
        productItem->setText(2, QString("%1 (%2)").arg(products[i]).arg(amounts[i]));
    }
}
