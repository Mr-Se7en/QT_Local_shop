#ifndef REGISTERADDDLG_H
#define REGISTERADDDLG_H

#include <QDialog>
#include <QMessageBox>
#include "producttablemodel.h"

namespace Ui {
class RegisterAddDlg;
}

class RegisterAddDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterAddDlg(ProductTableModel *model,QWidget *parent);
    ~RegisterAddDlg();
signals:
    void sendSelected(PRODUCT &a,int amount);
private slots:
    void onItemClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RegisterAddDlg *ui;
    ProductTableModel *modelPTR=nullptr;
    int currentrow=-1;
};

#endif // REGISTERADDDLG_H
