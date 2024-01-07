#include "confirmorderdialog.h"
#include "ui_confirmorderdialog.h"

ConfirmOrderDialog::ConfirmOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmOrderDialog)
{
    ui->setupUi(this);
}

ConfirmOrderDialog::~ConfirmOrderDialog()
{
    delete ui;
}

CUSTOMER ConfirmOrderDialog::getCustomerInfo() const
{
    // Retrieve information from UI elements and create a CUSTOMER object
    QString name = ui->lineEditName->text();
    QString id = ui->lineEditId->text();
    double creditAmount = ui->doubleSpinBoxCreditAmount->value();
    double debitAmount = ui->doubleSpinBoxDebitAmount->value();
    QString contactNumber = ui->lineEditContactNumber->text();
    QString address = ui->lineEditAddress->text();

    if (name.isEmpty() || contactNumber.isEmpty() || address.isEmpty() ||address.isEmpty()||contactNumber.isEmpty())
    {
        //error message
        ConfirmOrderDialog * nonConstThis = const_cast<ConfirmOrderDialog*>(this);
        QMessageBox::warning(nonConstThis, "Invalid Input", "Please enter valid values for all fields.");
        // Return an empty CUSTOMER object
        return CUSTOMER();
    }

    // Create a CUSTOMER object
    return CUSTOMER(id,name, creditAmount, debitAmount, contactNumber, address);
}

void ConfirmOrderDialog::setInitialTotalAmount(double totalAmount)
{
    ui->doubleSpinBoxTotalAmountPurchased->setValue(totalAmount);
}

double ConfirmOrderDialog::getTotalAmount() const
{
    double totalAmountPurchased = ui->doubleSpinBoxTotalAmountPurchased->value();
    return totalAmountPurchased;
}

double ConfirmOrderDialog::getAmountPaid() const
{
   double amountPaid = ui->doubleSpinBoxAmountPaid->value();
    return amountPaid;
}

void ConfirmOrderDialog::on_pushButton_clicked()
{
    // Validate the input and retrieve info
    CUSTOMER customer = getCustomerInfo();

    // Check if the customer information is not empty
    if (!customer.getId().isEmpty())
    {
        // If valid, accept the dialog
        accept();
        close();
    }
}


void ConfirmOrderDialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}

