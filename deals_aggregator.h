#ifndef DEALS_AGGREGATOR_H
#define DEALS_AGGREGATOR_H


#include "product.h"
#include "producttablemodel.h"
#include <QMessageBox>
class DealsAggregator : public QObject
{
    Q_OBJECT

public:
    DealsAggregator(ProductTableModel *inventoryModel,QObject *parent = nullptr);

public slots:
    void addDeal(const PRODUCT &wantedProduct, int wantedQuantity);
    void confirmLastDeal();
    void cancelLastDeal();
    void confirmorder();
    void removeitem(int);
    void EditItem(int row,PRODUCT ToBeEdited,int quantity);
    void discard();

signals:
    void ItemToRegister(PRODUCT &product, int quantity);
    void dealCanceled(const PRODUCT &wantedProduct, int wantedQuantity);
    void UpdateProduct(PRODUCT,int);
private:
    struct DealData
    {
        PRODUCT wanted;
        int wantedQuantity;
    };

    QVector<DealData> deals;
    ProductTableModel *inventoryModel;// Collection to store all deals
};

#endif // DEALS_AGGREGATOR_H
