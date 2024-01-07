#ifndef PRODUCTTABLEMODEL_H
#define PRODUCTTABLEMODEL_H

#include <QAbstractItemModel>

#include "product.h"

//test start
#include <QFile>
#include <QTextStream>
#include <QDebug>
//test end

class ProductTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ProductTableModel(QObject *parent = nullptr);

    QString getSavePath(){return inventory_save_filepath;};
    void setSavePath(QString);
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    void setProductList(const QVector<PRODUCT> &products);
    bool updateProduct(int row, const PRODUCT &product);
    void addProduct(const PRODUCT &product);
    bool removeProduct(int row);

    bool saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);

    PRODUCT getProduct(int row) const;

    int findProductIndex(const PRODUCT& product)const;

    QVector<PRODUCT> getList(){return productList;};

private:
    QVector<PRODUCT> productList;
    QString inventory_save_filepath="Inventory2.csv";
};

#endif // PRODUCTTABLEMODEL_H
