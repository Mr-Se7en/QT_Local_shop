#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "inventorywindow.h"
#include "logwindow.h"
#include "registerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager=new DataManager;
    inventoryModel = new ProductTableModel(this);
    registerModel=new RegisterProductModel(manager,this);
    customerModel=new CustomerTableModel(this);
    inventoryModel->loadFromFile("inventory.csv");
    manager->loadFromFile("manage.txt");
    customerModel->loadFromFile("customers.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}


void MainWindow::on_ExitButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to exit?");
    msgBox.setInformativeText("your progress is automatically saved upon closing");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        inventoryModel->saveToFile("inventory.csv");
        manager->saveToFile("manage.txt");
        customerModel->saveToFile("customers.txt");
        QCoreApplication::exit();
        break;
    case QMessageBox::Cancel:
        break;
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to exit?");
    msgBox.setInformativeText("your progress is automatically saved upon closing");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        inventoryModel->saveToFile("inventory.csv");
        manager->saveToFile("manage.txt");
        customerModel->saveToFile("customers.txt");
        QCoreApplication::exit();
        break;
    case QMessageBox::Cancel:
        event->ignore();
        break;
    }
}

void MainWindow::on_RegisterMenuButton_clicked()
{
    auto *register_menu=new registerWindow(customerModel,inventoryModel,registerModel);
    register_menu->Parent_pointer_set(this);
    register_menu->show();
//    hide();
}


void MainWindow::on_InventoryMenuButton_clicked()
{
    auto *inventory_menu=new inventoryWindow(manager,inventoryModel);
    inventory_menu->Parent_pointer_set(this);
    inventory_menu->show();
    hide();
}


void MainWindow::on_LogMenuButton_clicked()
{
    auto *log_menu=new LogWindow(manager,customerModel);
    log_menu->Parent_pointer_set(this);
    log_menu->show();
    hide();
}

