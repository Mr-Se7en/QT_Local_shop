#include "registeradddlg.h"
#include "ui_registeradddlg.h"

RegisterAddDlg::RegisterAddDlg(ProductTableModel *model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterAddDlg),modelPTR(model)
{
    ui->setupUi(this);
    ui->RegisterAddTableView->setModel(modelPTR);
    ui->RegisterAddTableView->update();
    connect(ui->RegisterAddTableView, &QTableView::clicked, this, &RegisterAddDlg::onItemClicked);
//    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &RegisterAddDlg::accept);
//    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &RegisterAddDlg::reject);
}

RegisterAddDlg::~RegisterAddDlg()
{
    delete ui;
}

void RegisterAddDlg::onItemClicked(const QModelIndex &index)
{
    int selectedRow = index.row();
    currentrow=selectedRow;
    int max=modelPTR->getProduct(currentrow).getQuantity();
    ui->spinBox->setMaximum(max);
    qDebug() << "Selected Row: " << selectedRow;

    // Get the selection model
    QItemSelectionModel *selectionModel = ui->RegisterAddTableView->selectionModel();

    // Clear the current selection
    selectionModel->clear();

    // Select the entire row
    for(int x=0;x<6;x++){
        selectionModel->select(index.siblingAtColumn(x), QItemSelectionModel::Select);
    }
    QVariant data = modelPTR->data(index, Qt::DisplayRole);
    qDebug() << "Data in clicked item: " << data;
}
void RegisterAddDlg::on_pushButton_clicked()
{
    if (currentrow != (-1) && ui->spinBox->value() != 0)
    {
        int amount = ui->spinBox->value();
        PRODUCT wanted = modelPTR->getProduct(currentrow);

        // Emit the signal
        emit sendSelected(wanted, amount);
        this->close();
    }
    else
    {
        // Handle the error
        QMessageBox::critical(this, "Input Error", "Invalid input. Please check your input fields.");
    }
}


void RegisterAddDlg::on_pushButton_2_clicked()
{
    this->close();
}

