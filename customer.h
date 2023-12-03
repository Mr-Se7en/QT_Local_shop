#include<string>
using namespace std;
#ifndef CUSTOMER_H
#define CUSTOMER_H


class CUSTOMER
{
public:
    CUSTOMER();
    CUSTOMER(string ,string ,double , double ,string ,string );
    //getters------------------------------------------------
    string getId() const { return CustomerId; }
    string getName() const { return customerName; }
    double getCreditAmount() const { return Credit_amount; }
    double getDebitAmount() const { return Debit_amount; }
    string getContactNumber() const { return Contact_number; }
    string getAddress() const { return Address; }
    //setters------------------------------------------------
    void setCreditAmount(double amount) { Credit_amount = amount; }
    void setDebitAmount(double amount) { Debit_amount = amount; }
private:
    string customerName;
    string CustomerId;
    double Credit_amount;
    double Debit_amount;
    string Contact_number;
    string Address;
};

#endif // CUSTOMER_H
