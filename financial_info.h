#ifndef FINANCIAL_INFO_H
#define FINANCIAL_INFO_H


class FINANCIAL_INFO
{
public:
    FINANCIAL_INFO();
    //getters------------------------------------------
    double getTotalCost() const { return totalCost; }
    double getTotalSales() const { return totalSales; }
    //setters------------------------------------------
    void addCost(double cost) { totalCost += cost; }
    void addSales(double sales) { totalSales += sales; }
private:
    double totalCost;
    double totalSales;
};

#endif // FINANCIAL_INFO_H
