#ifndef INVENTORYRESTOCKDLG_H
#define INVENTORYRESTOCKDLG_H

#include "product.h"
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class InventoryRestockDlg;
}

class InventoryRestockDlg : public QDialog
{
    Q_OBJECT

public:
    explicit InventoryRestockDlg(QWidget *parent = nullptr);
    ~InventoryRestockDlg();

    int getRestockQuantity();
private slots:
    void accept();
    void reject();
private:
    Ui::InventoryRestockDlg *ui;
};

#endif // INVENTORYRESTOCKDLG_H
