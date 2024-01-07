#include "registerproductmodel.h"

RegisterProductModel::RegisterProductModel(DataManager *manager,QObject *parent)
    : ProductTableModel(parent),
    manager(manager)
{
}

void RegisterProductModel::additem(PRODUCT &wantedProduct, int wantedQuantity)
{
    wantedProduct.setQuantity(wantedQuantity);
    addProduct(wantedProduct);
}
void RegisterProductModel::removeitem(int row){
    removeProduct(row);
}

void RegisterProductModel::confirmOrder(CUSTOMER customer)
{
    QDate time=QDate::currentDate();
    manager->addPurchase(customer.getName(),time,ProductTableModel::getList());
    double profit=0;
    for(PRODUCT &product:ProductTableModel::getList())
    {
        profit+=product.getPrice()*product.getQuantity();
    }
    manager->addIncome(profit);
    productList.clear();
    setProductList(productList);
}

void RegisterProductModel::UpdateProduct(PRODUCT toBeUPDATED, int Quantity)
{
    int index=findProductIndex(toBeUPDATED);
    toBeUPDATED.setQuantity(Quantity);
    updateProduct(index,toBeUPDATED);
}

double RegisterProductModel::getTotal()
{   double profit=0;
    for(PRODUCT &product:ProductTableModel::getList())
    {
        profit+=product.getPrice()*product.getQuantity();
    }
    return profit;
}
