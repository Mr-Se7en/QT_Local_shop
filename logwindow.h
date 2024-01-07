#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include "mainwindow.h"
#include "qitemselectionmodel.h"
#include <QMainWindow>

namespace Ui {
class LogWindow;
}

class LogWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogWindow(DataManager *manager,CustomerTableModel *customerTableModelPTR,QWidget *parent=nullptr);
    ~LogWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;

public slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onItemClicked(const QModelIndex &index);
private slots:
    void on_toolButton_3_triggered();

    void on_toolButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::LogWindow *ui;
    MainWindow *parent_pointer=nullptr;
    CustomerTableModel *customerTableModelPTR;
    DataManager *manager;
    int currentrow=-1;
};

#endif // LOGWINDOW_H
