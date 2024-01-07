// In your header file (e.g., SalesWidget.h)
#ifndef SALESWIDGET_H
#define SALESWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVector>
#include <QDate>

class SalesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SalesWidget(QWidget *parent = nullptr);

    // Add a function to add dates
    void addDate(const QDate &date);

    // Add a function to add purchases under a specific date
    void addPurchase(const QDate &date, const QString &customer, const QVector<QString> &products, const QVector<double> &amounts);


private:
    QTreeWidget *treeWidget;

    // Add a function to add a root item for Log
    void addLogRoot();

    // Add a function to find or create a date item under Log
    QTreeWidgetItem *findOrCreateDateItem(const QDate &date);

};

#endif // SALESWIDGET_H
