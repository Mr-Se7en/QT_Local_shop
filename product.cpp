#include "product.h"

PRODUCT::PRODUCT(){}
PRODUCT::PRODUCT(QString name,QString id, double price, int quantity, QString type, QString expDate)
    : productID(id), productName(name),
      price(price), quantity(quantity), productType(type),
      expiration_date(expDate)
{
}
PRODUCT PRODUCT::operator+(PRODUCT &B){
    PRODUCT A=*this;
    if(A==B){
        A.quantity+=B.quantity;
        return A;
    }
    else
        throw(std::invalid_argument("product mismatch"));
}
PRODUCT PRODUCT::operator-(PRODUCT &B){
    PRODUCT A=*this;
    if(A==B){
        A.quantity-=B.quantity;
        return A;
    }
    else
        throw(std::invalid_argument("product mismatch"));
}
bool PRODUCT::operator==(const PRODUCT& B)const {
    PRODUCT A=*this;
    return A.productName == B.productName &&
           A.productID == B.productID &&
           A.price == B.price &&
           A.productType == B.productType &&
           A.expiration_date == B.expiration_date;
}
