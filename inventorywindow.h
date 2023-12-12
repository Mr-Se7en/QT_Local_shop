#ifndef INVENTORYWINDOW_H
#define INVENTORYWINDOW_H


#include <QMainWindow>

#include "mainwindow.h"
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
private:
    Ui::inventoryWindow *ui;
    MainWindow *parent_pointer=nullptr;
};

#endif // INVENTORYWINDOW_H
