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
    explicit inventoryWindow(QWidget *parent = nullptr);
    ~inventoryWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_actionAdd_inventory_triggered();

private:
    Ui::inventoryWindow *ui;
    MainWindow *parent_pointer=nullptr;
    ProductTableModel *modelPTR=nullptr;
};

#endif // INVENTORYWINDOW_H
