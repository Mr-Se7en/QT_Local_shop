#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H


#include <QMainWindow>

#include "mainwindow.h"

#include "producttablemodel.h"
#include "qitemselectionmodel.h"

namespace Ui {
class inventoryWindow;
}

class inventoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventoryWindow(DataManager *manager,ProductTableModel *model=nullptr,QWidget *parent = nullptr);
    ~inventoryWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;
    void setModelPTR(ProductTableModel *modelPTR){modelPTR=modelPTR;}
public slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
private slots:
    void on_actionAdd_inventory_triggered();

    void on_actionRemove_inventory_triggered();

    void onItemClicked(const QModelIndex &index);

    void on_actionRestock_inventory_triggered();

    void on_actionEditInventory_triggered();

    void on_actionSave_triggered();

private:
    Ui::inventoryWindow *ui;
    MainWindow *parent_pointer=nullptr;
    ProductTableModel *modelPTR=nullptr;
    DataManager *manager;
    int currentrow=-1;

};

#endif // INVENTORYWINDOW_H
