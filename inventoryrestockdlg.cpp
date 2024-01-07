#include "inventoryrestockdlg.h"
#include "ui_inventoryrestockdlg.h"

InventoryRestockDlg::InventoryRestockDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InventoryRestockDlg)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &InventoryRestockDlg::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &InventoryRestockDlg::reject);
}

InventoryRestockDlg::~InventoryRestockDlg()
{
    delete ui;
}
int InventoryRestockDlg::getRestockQuantity()
{
    int quantity = ui->quantitySpinBox->value();

    // Input validation checks
    if (quantity <= 0)
    {
        throw std::invalid_argument("Invalid input. Please check your input fields.");
    }
    return quantity;

}

void InventoryRestockDlg::accept()
{
    qDebug() << "Accepting dialog...";

    try
    {
        // Validate the input
        int newProduct = getRestockQuantity();

        // If the input is valid, accept the dialog and close it
        QDialog::accept();
    }
    catch (const std::exception &e)
    {
        qDebug() << "Exception caught:" << e.what();

        // Display an error message box
        InventoryRestockDlg* nonConstThis = const_cast<InventoryRestockDlg*>(this);
        QMessageBox::critical(nonConstThis, "Input Error", QString("Error: %1").arg(e.what()));
    }

    qDebug() << "Dialog accepted.";
}

void InventoryRestockDlg::reject()
{
    QDialog::reject();
}
