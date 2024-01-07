#include "customer.h"

CUSTOMER::CUSTOMER()
{

}

CUSTOMER::CUSTOMER(QString id,QString name,
           double credit, double debit,QString contact,
          QString addr)
    : CustomerId(id), customerName(name),
      Credit_amount(credit), Debit_amount(debit), Contact_number(contact),
      Address(addr)
      {

}

bool CUSTOMER::operator==(const CUSTOMER &rhs) const
{
  return this->getId() == rhs.getId() &&
         this->getName() == rhs.getName() &&
         this->getContactNumber() == rhs.getContactNumber() &&
         this->getAddress() == rhs.getAddress();
}

