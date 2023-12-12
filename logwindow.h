#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include "mainwindow.h"
#include <QMainWindow>

namespace Ui {
class LogWindow;
}

class LogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = nullptr);
    ~LogWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::LogWindow *ui;
    MainWindow *parent_pointer=nullptr;
};

#endif // LOGWINDOW_H
