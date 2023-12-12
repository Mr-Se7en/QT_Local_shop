#include "inventorywindow.h"
#include "ui_inventorywindow.h"

inventoryWindow::inventoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inventoryWindow)
{
    ui->setupUi(this);
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
