#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H


#include <QMainWindow>

#include "mainwindow.h"

#include "producttablemodel.h"

namespace Ui {
class inventoryWindow;
}

class inventoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventoryWindow(ProductTableModel *model=nullptr,QWidget *parent = nullptr);
    ~inventoryWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;
    void setModelPTR(ProductTableModel *modelPTR){modelPTR=modelPTR;}
private slots:
    void on_actionAdd_inventory_triggered();

    void on_actionRemove_inventory_triggered();

    void onItemClicked(const QModelIndex &index);

    void on_actionRestock_inventory_triggered();

    void on_actionEditInventory_triggered();

private:
    Ui::inventoryWindow *ui;
    MainWindow *parent_pointer=nullptr;
    ProductTableModel *modelPTR=nullptr;
    int currentrow=-1;
};

#endif // INVENTORYWINDOW_H
