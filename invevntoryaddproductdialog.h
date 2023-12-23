#ifndef INVEVNTORYADDPRODUCTDIALOG_H
#define INVEVNTORYADDPRODUCTDIALOG_H

#include "product.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class InvevntoryAddProductDialog;
}

class InvevntoryAddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InvevntoryAddProductDialog(QWidget *parent = nullptr);
    explicit InvevntoryAddProductDialog(const PRODUCT &product,QWidget *parent = nullptr);
    ~InvevntoryAddProductDialog();
    PRODUCT getProduct() const;
private slots:
    void accept();
    void reject();

private:
    Ui::InvevntoryAddProductDialog *ui;
    bool isEditMode;
};

#endif // INVEVNTORYADDPRODUCTDIALOG_H
