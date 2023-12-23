#include "invevntoryaddproductdialog.h"
#include "ui_invevntoryaddproductdialog.h"

InvevntoryAddProductDialog::InvevntoryAddProductDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::InvevntoryAddProductDialog), isEditMode(false)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &InvevntoryAddProductDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &InvevntoryAddProductDialog::reject);
}

// Constructor for edit mode
InvevntoryAddProductDialog::InvevntoryAddProductDialog(const PRODUCT &product, QWidget *parent)
    : QDialog(parent), ui(new Ui::InvevntoryAddProductDialog), isEditMode(true)
{
    ui->setupUi(this);

    // Set the default values for line edits and spin boxes
    ui->productNameLineEdit->setText(product.getproductName());
    ui->productIdLineEdit->setText(product.getId());
    ui->priceDoubleSpinBox->setValue(product.getPrice());
    ui->quantitySpinBox->setValue(product.getQuantity());
    ui->productTypeLineEdit->setText(product.getType());
    ui->expirationDateLineEdit->setText(product.getExpirationDate());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &InvevntoryAddProductDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &InvevntoryAddProductDialog::reject);
}

InvevntoryAddProductDialog::~InvevntoryAddProductDialog()
{
    delete ui;
}
PRODUCT InvevntoryAddProductDialog::getProduct() const
{

        // Retrieve product information from the dialog's input fields
        QString productName = ui->productNameLineEdit->text();
        QString productId = ui->productIdLineEdit->text();
        double price = ui->priceDoubleSpinBox->value();
        int quantity = ui->quantitySpinBox->value();
        QString productType = ui->productTypeLineEdit->text();
        QString expirationDate = ui->expirationDateLineEdit->text();

        // Input validation checks
        if (productName.isEmpty() || productId.isEmpty() || quantity <= 0 || price <= 0)
        {
            throw std::invalid_argument("Invalid input. Please check your input fields.");
        }

        // Create and return a new PRODUCT object
        return PRODUCT(productName, productId, price, quantity, productType, expirationDate);

}
void InvevntoryAddProductDialog::accept()
{
        qDebug() << "Accepting dialog...";

        try
        {
            // Validate the input or perform additional checks if needed
            PRODUCT newProduct = getProduct();

            // If the input is valid, accept the dialog and close it
            QDialog::accept();
        }
        catch (const std::exception &e)
        {
            qDebug() << "Exception caught:" << e.what();

            // Display an error message box
            InvevntoryAddProductDialog* nonConstThis = const_cast<InvevntoryAddProductDialog*>(this);
            QMessageBox::critical(nonConstThis, "Input Error", QString("Error: %1").arg(e.what()));
        }

        qDebug() << "Dialog accepted.";
}

void InvevntoryAddProductDialog::reject()
{
    // Reject the dialog and close it
    QDialog::reject();
}
