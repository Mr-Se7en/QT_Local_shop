#include "deals_aggregator.h"

DealsAggregator::DealsAggregator(ProductTableModel *inventoryModel,QObject *parent) : QObject(parent)
    ,inventoryModel(inventoryModel)
{

}

void DealsAggregator::addDeal(const PRODUCT &wantedProduct, int wantedQuantity)
{
    // Check for duplicates
    for (DealData &existingDeal : deals)
    {
        if (existingDeal.wanted == wantedProduct)
        {
            // Duplicate found, update the wanted quantity
            existingDeal.wantedQuantity += wantedQuantity;

            // Check if the updated quantity exceeds the inventory
            int inventoryQuantity = wantedProduct.getQuantity();
            if (existingDeal.wantedQuantity > inventoryQuantity)
            {
                // If exceeded, set the wanted quantity to the maximum in the inventory
                existingDeal.wantedQuantity = inventoryQuantity;

                // Notify the user about the limit via QMessageBox
                QMessageBox::warning(nullptr, "Quantity Exceeded", "The wanted quantity exceeds the available inventory. Set to maximum.");
            }

            // Emit the update product signal
            emit UpdateProduct(existingDeal.wanted, existingDeal.wantedQuantity);

            return; // Exit the function since the deal is already in the list
        }
    }

    // No duplicate found, add a new deal to the list
    DealData deal;
    deal.wanted = wantedProduct;
    deal.wantedQuantity = wantedQuantity;
    deals.append(deal);

    // Emit the signal for the new deal
    emit ItemToRegister(deal.wanted, deal.wantedQuantity);
}

void DealsAggregator::confirmLastDeal()
{
    if (!deals.isEmpty())
    {
        DealData lastDeal = deals.last();
        int productIndex = inventoryModel->findProductIndex(lastDeal.wanted);

        if (productIndex != -1)
        {
            PRODUCT modifiedProduct = lastDeal.wanted;
            modifiedProduct.setQuantity(lastDeal.wanted.getQuantity() - lastDeal.wantedQuantity);

            inventoryModel->updateProduct(productIndex, modifiedProduct);

            deals.removeLast();
        }
    }
}

void DealsAggregator::cancelLastDeal()
{
    if (!deals.isEmpty())
    {
        DealData lastDeal = deals.last();
        int productIndex = inventoryModel->findProductIndex(lastDeal.wanted);

        if (productIndex != -1)
        {
            inventoryModel->updateProduct(productIndex, lastDeal.wanted);

            emit dealCanceled(lastDeal.wanted, lastDeal.wantedQuantity);

            deals.removeLast();
        }
    }
}

void DealsAggregator::confirmorder()
{
    for (const DealData &deal : deals)
{
    int productIndex = inventoryModel->findProductIndex(deal.wanted);
    if (productIndex != -1)
    {
        // If the product is found, update the quantity
        PRODUCT updatedProduct = inventoryModel->getProduct(productIndex);
        updatedProduct.setQuantity(updatedProduct.getQuantity() - deal.wantedQuantity);

        // Check if the quantity is zero, and remove the product if needed
        if (updatedProduct.getQuantity() <= 0)
        {
            inventoryModel->removeProduct(productIndex);
        }
        else
        {
            // Update the product if the quantity is greater than zero
            inventoryModel->updateProduct(productIndex, updatedProduct);
        }
    }
}

// Clear the deals vector after confirming
deals.clear();
}

void DealsAggregator::removeitem(int a)
{
deals.removeAt(a);
}

void DealsAggregator::EditItem(int row, PRODUCT ToBeEdited, int quantity)
{
if (row < 0 || row >= deals.size())
    return; // Invalid row index

DealData &deal = deals[row];

// Find the index of the product in the deal
int productIndex = -1;
// Check if the new quantity exceeds the inventory quantity
int inventoryQuantity = deal.wanted.getQuantity();
if (quantity > inventoryQuantity)
{
    // Set the quantity to the maximum inventory quantity
    quantity = inventoryQuantity;

    // Alert the user (you can replace this with your actual alert mechanism)
    QMessageBox::warning(nullptr, "Warning", "Quantity exceeds inventory quantity. Set to maximum.");
}

// Update the quantity
deal.wantedQuantity = quantity;

// Emit the signal with the updated product and quantity
emit UpdateProduct(ToBeEdited, quantity);

}

void DealsAggregator::discard()
{
deals.clear();
}
