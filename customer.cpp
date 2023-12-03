#include "customer.h"

CUSTOMER::CUSTOMER(string id,string name,
           double credit, double debit,string contact,
          string addr)
    : CustomerId(id), customerName(name),
      Credit_amount(credit), Debit_amount(debit), Contact_number(contact),
      Address(addr)
      {

      };
