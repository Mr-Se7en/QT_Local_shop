#include "product.h"

PRODUCT::PRODUCT(string id, string name, double price, int quantity, string type, string expDate)
    : productID(id), productName(name),
      price(price), quantity(quantity), productType(type),
      expiration_date(expDate)
{
}
