#include "financialreport.h"
#include "ui_financialreport.h"

FinancialReport::FinancialReport(DataManager *manager,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinancialReport),
    manager(manager)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(manager->getIncome()));
    ui->lineEdit_2->setText(QString::number(manager->getexpense()));
    ui->lineEdit_3->setText(QString::number(manager->getIncome()-manager->getexpense()));
}

FinancialReport::~FinancialReport()
{
    delete ui;
}

void FinancialReport::on_pushButton_clicked()
{
    close();
}

