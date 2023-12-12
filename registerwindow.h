#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>

#include "mainwindow.h"

namespace Ui {
class registerWindow;
}

class registerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit registerWindow(QWidget *parent = nullptr);
    ~registerWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::registerWindow *ui;
    MainWindow *parent_pointer=nullptr;
};

#endif // REGISTERWINDOW_H