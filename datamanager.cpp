#include "datamanager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

DataManager::DataManager() {}

void DataManager::addPurchase(const QString &customer, const QDate &date, const QVector<PRODUCT> &products) {
    Purchase newPurchase;
    newPurchase.customerName = customer;
    newPurchase.date = date;
    newPurchase.products = products;
    purchases.append(newPurchase);
}


QVector<Purchase> DataManager::getAllPurchases() const {
    return purchases;
}

void DataManager::saveToFile(const QString &filename) const {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        // Save each purchase entry
        for (const auto &purchase : purchases) {
            out << "Customer: " << purchase.customerName << "\n";
            out << "Date: " << purchase.date.toString(Qt::ISODate) << "\n";

            // Save each product in the purchase
            for (const auto &product : purchase.products) {
                out << "Product: " << product.serialize() << "\n";
            }

            out << "\n";
        }

        file.close();
    }
}

void DataManager::loadFromFile(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        purchases.clear();

        // Load each purchase entry
        while (!in.atEnd()) {
            Purchase purchase;
            QString line = in.readLine();

            // Read customer name
            if (line.startsWith("Customer: ")) {
                purchase.customerName = line.mid(10);
            }

            // Read date
            line = in.readLine();
            if (line.startsWith("Date: ")) {
                purchase.date = QDate::fromString(line.mid(6), Qt::ISODate);
            }

            // Read products
            while (!in.atEnd()) {
                line = in.readLine();
                if (line.startsWith("Product: ")) {
                    PRODUCT product;
                    product.deserialize(line.mid(9));
                    purchase.products.append(product);
                } else {
                    break;
                }
            }

            purchases.append(purchase);
        }

        file.close();
    }
}
