#ifndef FINANCIALREPORT_H
#define FINANCIALREPORT_H

#include "datamanager.h"
#include <QDialog>

namespace Ui {
class FinancialReport;
}

class FinancialReport : public QDialog
{
    Q_OBJECT

public:
    explicit FinancialReport(DataManager *manager,QWidget *parent = nullptr);
    ~FinancialReport();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FinancialReport *ui;
    DataManager *manager;
};

#endif // FINANCIALREPORT_H
