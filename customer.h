#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<QString>

class CUSTOMER
{
public:
    CUSTOMER();
    CUSTOMER(QString ,QString ,double , double ,QString ,QString );
    //getters------------------------------------------------
    QString getId() const { return CustomerId; }
    QString getName() const { return customerName; }
    double getCreditAmount() const { return Credit_amount; }
    double getDebitAmount() const { return Debit_amount; }
    QString getContactNumber() const { return Contact_number; }
    QString getAddress() const { return Address; }
    //setters------------------------------------------------
    void setCreditAmount(double amount) { Credit_amount = amount; }
    void setDebitAmount(double amount) { Debit_amount = amount; }
    bool operator==(const CUSTOMER& rhs)const;
private:
    QString customerName;
    QString CustomerId;
    double Credit_amount;
    double Debit_amount;
    QString Contact_number;
    QString Address;
};

#endif // CUSTOMER_H
