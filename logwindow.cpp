#include "logwindow.h"
#include "confirmorderdialog.h"
#include "customertablemodel.h"
#include "financialreport.h"
#include "qdatetime.h"
#include "saleswidget.h"
#include "ui_logwindow.h"

LogWindow::LogWindow(DataManager *manager,CustomerTableModel *customerTableModelPTR,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogWindow),
    customerTableModelPTR(customerTableModelPTR),
    manager(manager)
{
    ui->setupUi(this);
    ui->Customer_tableView_2->setModel(customerTableModelPTR);
    QVector<Purchase> purchases=manager->getAllPurchases();
    auto salesWidget = new SalesWidget(this);
    ui->horizontalLayout->addWidget(salesWidget);
    for(Purchase &purchase:purchases)
    {
        QVector<QString>Products;
        QVector<double>amount;
        for(PRODUCT &x:purchase.products)
        {
            Products.push_back(x.getproductName());
        }
        for(PRODUCT &x:purchase.products)
        {
            amount.push_back(x.getQuantity());
        }
       salesWidget->addPurchase(purchase.date,purchase.customerName,Products,amount);
    }
    connect(ui->Customer_tableView_2, &QTableView::clicked, this, &LogWindow::onItemClicked);
    connect(ui->Customer_tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LogWindow::onSelectionChanged);
}

LogWindow::~LogWindow()
{
    delete ui;
}

void LogWindow::closeEvent(QCloseEvent *event)
{
    parent_pointer->show();
    QMainWindow::closeEvent(event);
}

void LogWindow::onItemClicked(const QModelIndex &index)
{
    disconnect(ui->Customer_tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LogWindow::onSelectionChanged);
    int selectedRow = index.row();
    currentrow = selectedRow;
    qDebug() << "Selected Row: " << selectedRow;

    // Get the selection model
    QItemSelectionModel *selectionModel = ui->Customer_tableView_2->selectionModel();

    // Clear the current selection
    selectionModel->clear();

    // Select the entire row
    for (int x = 0; x < 6; x++) {
       selectionModel->select(index.siblingAtColumn(x), QItemSelectionModel::Select);
    }
    QVariant data = customerTableModelPTR->data(index, Qt::DisplayRole);
    qDebug() << "Data in clicked item: " << data;

    // Reconnect the selectionChanged signal
    connect(ui->Customer_tableView_2->selectionModel(), &QItemSelectionModel::selectionChanged, this, &LogWindow::onSelectionChanged);
}

void LogWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // Check if any items are selected
    if (selected.indexes().isEmpty()) {
       // No item selected, reset currentrow
       currentrow = -1;
    } else {
       // Get the selected row
       int selectedRow = selected.indexes().first().row();
       currentrow = selectedRow;
       qDebug() << "Selected Row: " << selectedRow;
    }
}

void LogWindow::on_toolButton_3_triggered()
{}

void LogWindow::on_toolButton_3_clicked()
{
    customerTableModelPTR->removeCustomer(currentrow);
    currentrow=-1;
}


void LogWindow::on_pushButton_clicked()
{
    FinancialReport *report=new FinancialReport(manager,this);
    report->exec();
}


void LogWindow::on_toolButton_4_clicked()
{
    CUSTOMER toBeEdited=customerTableModelPTR->getCustomer(currentrow);
    ConfirmOrderDialog *editor=new ConfirmOrderDialog(true,toBeEdited);
    if (editor->exec() == QDialog::Accepted)
    {
       CUSTOMER Customer = editor->getCustomerInfo();
       customerTableModelPTR->updateCustomer(currentrow,Customer);
    }
}

