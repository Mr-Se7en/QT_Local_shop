#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "producttablemodel.h"
#include "registerproductmodel.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>

//#include "registerwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void closeEvent (QCloseEvent *event) override;
    ~MainWindow();

private slots:
    void on_ExitButton_clicked();

    void on_RegisterMenuButton_clicked();

    void on_InventoryMenuButton_clicked();

    void on_LogMenuButton_clicked();

private:
    Ui::MainWindow *ui;
    ProductTableModel *inventoryModel;
    RegisterProductModel *registerModel;
};
#endif // MAINWINDOW_H
