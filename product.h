#include <string>
using namespace std;
#ifndef PRODUCT_H
#define PRODUCT_H

class PRODUCT
{
public:
    PRODUCT();
    PRODUCT(string, string, double, int, string, string);
    // getters------------------------------------------------
    string getproductName() const { return productName; };
    string getId() const { return productID; };
    double getPrice() const { return price; };
    int getQuantity() const { return quantity; };
    string getType() const { return productType; };
    string getExpirationDate() const { return expiration_date; };
    // setters------------------------------------------------
    void setPrice(double p) { price = p; };
    void setQuantity(int q) { quantity = q; };

private:
    string productName;
    string productID;
    double price;
    int quantity;
    string productType;
    string expiration_date;
};

#endif // PRODUCT_H
