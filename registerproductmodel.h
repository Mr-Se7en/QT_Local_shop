#ifndef REGISTERPRODUCTMODEL_H
#define REGISTERPRODUCTMODEL_H

#include "product.h"
#include "producttablemodel.h"
#include <QAbstractTableModel>

class RegisterProductModel : public ProductTableModel
{
    Q_OBJECT

public:
    explicit RegisterProductModel(QObject *parent = nullptr);
public slots:
    void additem(PRODUCT &product, int quantity);
    void removeitem(int row);
    void confirmOrder();
    void UpdateProduct(PRODUCT toBeUPDATED, int Quantity);
private:
    QVector<PRODUCT> productList;
};

#endif // REGISTERPRODUCTMODEL_H
