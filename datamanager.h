#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector>
#include <QDate>
#include <QString>
#include "product.h"

struct Purchase {
    QString customerName;
    QDate date;
    QVector<PRODUCT> products;
};

class DataManager {
public:
    DataManager();

    void addPurchase(const QString &customer, const QDate &date, const QVector<PRODUCT> &products);

    QVector<Purchase> getAllPurchases() const;

    void saveToFile(const QString &filename) const;

    void loadFromFile(const QString &filename);

    void addIncome(double to_be_added){income+=to_be_added;};
    void addExpence(double to_be_added){expense+=to_be_added;};

    double getIncome(){return income;};
    double getexpense(){return expense;};

private:
    QVector<Purchase> purchases;
    double expense=0;
    double income=0;
};

#endif // DATAMANAGER_H
