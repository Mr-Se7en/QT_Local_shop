#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>

#include "deals_aggregator.h"
#include "mainwindow.h"
#include "qitemselectionmodel.h"
#include "registeradddlg.h"
#include "registerproductmodel.h"

namespace Ui {
class registerWindow;
}

class registerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit registerWindow(ProductTableModel *inventory_model=nullptr,RegisterProductModel *register_model=nullptr,QWidget *parent = nullptr);
    ~registerWindow();

    void Parent_pointer_set(MainWindow *a){parent_pointer=a;};
    void closeEvent(QCloseEvent *event) override;
private slots:
    void on_actionADD_triggered();
    void on_actionRemove_triggered();
    void onItemClicked(const QModelIndex &index);

    void on_actionConfirm_order_triggered();

    void on_actionEdit_triggered();

    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_actionDiscard_triggered();

signals:
    void removeitem(int row);
    void confirmOrder();
    void EditItem(int row,PRODUCT ToBeEdited,int quantity);
    void discard();
private:
    Ui::registerWindow *ui;
    MainWindow *parent_pointer=nullptr;
    ProductTableModel *inventory_model;
    RegisterProductModel *registerPTR;
    DealsAggregator* dealsAggregator;
    RegisterAddDlg *addProductDialog;
    int currentrow=-1;
};

#endif // REGISTERWINDOW_H
