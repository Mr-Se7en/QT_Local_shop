#include "product.h"

PRODUCT::PRODUCT(QString id, QString name, double price, int quantity, QString type, QString expDate)
    : productID(id), productName(name),
      price(price), quantity(quantity), productType(type),
      expiration_date(expDate)
{
}
