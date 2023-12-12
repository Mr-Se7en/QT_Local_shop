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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ExitButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Do you want to exit?");
//    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
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
//    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        QCoreApplication::exit();
        break;
    case QMessageBox::Cancel:
        event->ignore();
        break;
    }
}

void MainWindow::on_RegisterMenuButton_clicked()
{
    auto *register_menu=new registerWindow(this);
    register_menu->Parent_pointer_set(this);
    register_menu->show();
    hide();
}


void MainWindow::on_InventoryMenuButton_clicked()
{
    auto *inventory_menu=new inventoryWindow(this);
    inventory_menu->Parent_pointer_set(this);
    inventory_menu->show();
    hide();
}


void MainWindow::on_LogMenuButton_clicked()
{
    auto *log_menu=new LogWindow(this);
    log_menu->Parent_pointer_set(this);
    log_menu->show();
    hide();
}

