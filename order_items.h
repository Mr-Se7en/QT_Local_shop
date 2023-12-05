#include"product.h"
#ifndef ORDER_ITEMS_H
#define ORDER_ITEMS_H


class ORDER_ITEMS
{
public:
    ORDER_ITEMS(PRODUCT,int);
private:
    PRODUCT product;
    int quantity;
};

#endif // ORDER_ITEMS_H
