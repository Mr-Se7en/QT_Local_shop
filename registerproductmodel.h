#ifndef REGISTERPRODUCTMODEL_H
#define REGISTERPRODUCTMODEL_H

#include "customer.h"
#include "datamanager.h"
#include "product.h"
#include "producttablemodel.h"
#include <QAbstractTableModel>

class RegisterProductModel : public ProductTableModel
{
    Q_OBJECT

public:
    explicit RegisterProductModel(DataManager *manager,QObject *parent = nullptr);
public slots:
    void additem(PRODUCT &product, int quantity);
    void removeitem(int row);
    void confirmOrder(CUSTOMER customer);
    void UpdateProduct(PRODUCT toBeUPDATED, int Quantity);
    double getTotal();
private:
    QVector<PRODUCT> productList;
    DataManager *manager;
};

#endif // REGISTERPRODUCTMODEL_H
