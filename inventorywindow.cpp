#include "inventorywindow.h"
#include "ui_inventorywindow.h"

#include"producttablemodel.h"

inventoryWindow::inventoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inventoryWindow)
{
    ui->setupUi(this);

    modelPTR = new ProductTableModel(this);

    ui->tableView->setModel(modelPTR);
//    ui->tableView->update();


}

inventoryWindow::~inventoryWindow()
{
    delete ui;
}

void inventoryWindow::closeEvent(QCloseEvent *event)
{
    parent_pointer->show();
    QMainWindow::closeEvent(event);
}

void inventoryWindow::on_actionAdd_inventory_triggered()
{
    PRODUCT test("banana", "help", 69.69, 7, "me", "god");
    modelPTR->addProduct(test);
    ui->tableView->update();

}

