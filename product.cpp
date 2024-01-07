#include "product.h"
#include <QStringList>

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

QString PRODUCT::serialize() const {
    // Serialize product information as a string
    return productName + "|" + productID + "|" + QString::number(price) + "|" +
           QString::number(quantity) + "|" + productType + "|" + expiration_date;
}

void PRODUCT::deserialize(const QString &data) {
    // Deserialize product information from a string
    QStringList parts = data.split("|");
    if (parts.size() == 6) {
        productName = parts[0];
        productID = parts[1];
        price = parts[2].toDouble();
        quantity = parts[3].toInt();
        productType = parts[4];
        expiration_date = parts[5];
    }
}

QDate PRODUCT::String2Date()const
{
    QDate dated=QDate::fromString(expiration_date, Qt::ISODate);
    return dated;
}
