#ifndef CONFIRMORDERDIALOG_H
#define CONFIRMORDERDIALOG_H

#include "customer.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ConfirmOrderDialog;
}

class ConfirmOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmOrderDialog(QWidget *parent = nullptr);
    ~ConfirmOrderDialog();

    //retrieve entered customer information
    CUSTOMER getCustomerInfo() const;

    //set the initial value of the total amount spinbox
    void setInitialTotalAmount(double totalAmount);

    //retrieve the total amount
    double getTotalAmount() const;

    //retrieve the amount paid
    double getAmountPaid() const;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ConfirmOrderDialog *ui;
};

#endif // CONFIRMORDERDIALOG_H
