#include "registerproductmodel.h"

RegisterProductModel::RegisterProductModel(QObject *parent)
    : ProductTableModel(parent)
{
}

//QVariant RegisterProductModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//int RegisterProductModel::rowCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//int RegisterProductModel::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    // FIXME: Implement me!
//}

//QVariant RegisterProductModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    // FIXME: Implement me!
//    return QVariant();
//}

void RegisterProductModel::additem(PRODUCT &wantedProduct, int wantedQuantity)
{
    wantedProduct.setQuantity(wantedQuantity);
    addProduct(wantedProduct);
}
void RegisterProductModel::removeitem(int row){
    removeProduct(row);
}

void RegisterProductModel::confirmOrder()
{
    productList.clear();
    setProductList(productList);
}

void RegisterProductModel::UpdateProduct(PRODUCT toBeUPDATED, int Quantity)
{
    int index=findProductIndex(toBeUPDATED);
    toBeUPDATED.setQuantity(Quantity);
    updateProduct(index,toBeUPDATED);
}
