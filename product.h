
#ifndef PRODUCT_H
#define PRODUCT_H
#include <QString>
using namespace Qt;
class PRODUCT
{
public:
    PRODUCT();
    PRODUCT(QString, QString, double, int, QString, QString);
    // getters------------------------------------------------
    QString getproductName() const { return productName; };
    QString getId() const { return productID; };
    double getPrice() const { return price; };
    int getQuantity() const { return quantity; };
    QString getType() const { return productType; };
    QString getExpirationDate() const { return expiration_date; };
    // setters------------------------------------------------
    void setPrice(double p) { price = p; };
    void setQuantity(int q) { quantity = q; };
    PRODUCT operator+(PRODUCT &obj);
    PRODUCT operator-(PRODUCT &obj);
    bool operator==(const PRODUCT& B);
private:
    QString productName;
    QString productID;
    double price;
    int quantity;
    QString productType;
    QString expiration_date;
};

#endif // PRODUCT_H
